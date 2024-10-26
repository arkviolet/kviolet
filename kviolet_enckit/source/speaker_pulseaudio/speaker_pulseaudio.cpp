#include "speaker_pulseaudio.h"

#include <glog/logging.h>
#include <sndfile.h>

#include "kviolet/utilities/timestamp.h"

namespace kviolet {
namespace enckit {

class AudioStream {
 public:
  AudioStream(const std::string &task_id) : is_pause_{false},
                                            is_cancel_{false},
                                            is_running_{true},
                                            task_id_(task_id),
                                            sndfile_{nullptr},
                                            stream_{nullptr} {}

  ~AudioStream() { Close(); }

 public:
  bool Start(pa_context *context, const std::string &path, int volume) {
    SF_INFO sfi;
    sndfile_ = sf_open(path.c_str(), SFM_READ, &sfi);
    if (!sndfile_) {
      LOG(ERROR) << "open video file error:" << path;
      return false;
    }

    pa_cvolume cvolume;
    auto sample_spec = AudioFormat(sfi);
    stream_ = pa_stream_new(context, task_id_.c_str(), &sample_spec, nullptr);
    if (!stream_) {
      LOG(ERROR) << "create stream error";
      return false;
    }
    pa_stream_set_write_callback(stream_, stream_request_cb, this);
    pa_stream_set_state_callback(stream_, stream_state_callback, this);

    pa_cvolume_set(&cvolume, sample_spec.channels, (pa_volume_t) (((double) volume / 100) * PA_VOLUME_NORM));
    if (0 != pa_stream_connect_playback(stream_, nullptr, NULL, PA_STREAM_NOFLAGS, &cvolume, nullptr)) {
      LOG(ERROR) << "connect playback error";
      return false;
    }
    return true;
  }

  void Pause() { is_pause_ = true; }

  void Resume() {
    if (stream_) {
      is_pause_ = false;
      pa_stream_cork(stream_, 0, nullptr, nullptr);
    };
  }

  void Cancel() { is_cancel_ = true; }

  bool IsRunning() { return is_running_; }

 protected:
  void Close() {
    if (stream_) {
      LOG(WARNING) << task_id_ << ",stream is close";
      pa_stream_set_write_callback(stream_, nullptr, nullptr);
      pa_stream_set_state_callback(stream_, nullptr, nullptr);
      pa_stream_disconnect(stream_);
      pa_stream_unref(stream_);
      stream_ = nullptr;
    }

    if (sndfile_) {
      sf_close(sndfile_);
      sndfile_ = nullptr;
    }

    is_running_ = false;
  }

  pa_sample_spec AudioFormat(const SF_INFO &sfi) {
    pa_sample_spec sample_spec = {PA_SAMPLE_S16LE, 44100, 2};
    switch (sfi.format & SF_FORMAT_SUBMASK) {
      case SF_FORMAT_PCM_16:
      case SF_FORMAT_PCM_U8:
      case SF_FORMAT_PCM_S8:sample_spec.format = PA_SAMPLE_S16NE;
        break;
      case SF_FORMAT_PCM_32:
      case SF_FORMAT_PCM_24:
        /* note that libsndfile will convert 24 bits samples to 32 bits
         * when using the sf_readf_int function, which will be selected
         * by setting the format to s32. */
        sample_spec.format = PA_SAMPLE_S32NE;
        break;
      case SF_FORMAT_ULAW:sample_spec.format = PA_SAMPLE_ULAW;
        break;
      case SF_FORMAT_ALAW:sample_spec.format = PA_SAMPLE_ALAW;
        break;
      case SF_FORMAT_FLOAT:
      case SF_FORMAT_DOUBLE:
      default:sample_spec.format = PA_SAMPLE_FLOAT32NE;
        break;
    }
    sample_spec.rate = (uint32_t) sfi.samplerate;
    sample_spec.channels = (uint8_t) sfi.channels;
    return sample_spec;
  }

  static void stream_state_callback(pa_stream *s, void *userdata) {
    auto *thiz = reinterpret_cast<AudioStream *>(userdata);
    switch (pa_stream_get_state(s)) {
      case PA_STREAM_CREATING:
      case PA_STREAM_TERMINATED:break;
      case PA_STREAM_READY:LOG(WARNING) << thiz->task_id_ << ",stream is ready";
        break;
      case PA_STREAM_FAILED:
      default:LOG(ERROR) << thiz->task_id_ << ",stream error:"
                         << pa_strerror(pa_context_errno(pa_stream_get_context(s)));
        break;
    }
  }

  static void stream_request_cb(pa_stream *s, size_t length, void *userdata) {
    void *data;
    sf_count_t bytes;
    auto *thiz = reinterpret_cast<AudioStream *>(userdata);
    for (;;) {
      size_t data_length = length;
      if (pa_stream_begin_write(s, &data, &data_length) < 0) {
        LOG(ERROR) << thiz->task_id_ << ":memory error";
        thiz->Close();
        return;
      }

      bytes = sf_read_raw(thiz->sndfile_, data, (sf_count_t) data_length);
      if (bytes > 0) {
        pa_stream_write(s, data, (size_t) bytes, NULL, 0, PA_SEEK_RELATIVE);
      } else {
        pa_stream_cancel_write(s);
      }

      // EOF?
      if (bytes < (sf_count_t) data_length) {
        pa_operation *o;
        pa_stream_set_write_callback(s, NULL, NULL);
        if (!(o = pa_stream_drain(s, stream_drain_complete, userdata))) {
          LOG(ERROR) << thiz->task_id_ << ":" << pa_strerror(pa_context_errno(pa_stream_get_context(s)));
          thiz->Close();
          return;
        }
        pa_operation_unref(o);
        break;
      }

      // Request fulfilled
      if ((size_t) bytes >= length) {
        break;
      }

      length -= bytes;
    }

    if (thiz->is_pause_) {
      pa_stream_cork(s, 1, nullptr, nullptr);
    }

    if (thiz->is_cancel_) {
      LOG(ERROR) << thiz->task_id_ << ":cancel audio";
      thiz->Close();
    }
  }

  static void stream_drain_complete(pa_stream *, int success, void *userdata) {
    auto *thiz = reinterpret_cast<AudioStream *>(userdata);
    LOG(WARNING) << thiz->task_id_ << ",success:" << success;
    thiz->Close();
  }

 private:
  bool is_pause_;
  bool is_cancel_;
  bool is_running_;
  std::string task_id_;
  SNDFILE *sndfile_;
  pa_stream *stream_;
};

void PulseAudioManager::Start() {
  LOG(WARNING) << "pulseaudio start";
  context_is_connect_ = false;
  mainloop_ = pa_mainloop_new();
  if (!mainloop_) {
    LOG(ERROR) << "pa_mainloop_new error";
    return;
  }

  auto mainloop_api = pa_mainloop_get_api(mainloop_);
  context_ = pa_context_new(mainloop_api, "playback");
  if (!context_) {
    LOG(ERROR) << "pa_context_new error";
    return;
  }

  pa_context_set_state_callback(context_, context_state_callback, this);
  pa_context_connect(context_, nullptr, PA_CONTEXT_NOFLAGS, nullptr);

  loop_thread_.reset(new std::thread([this]() {
    pa_mainloop_run(mainloop_, nullptr);
    LOG(WARNING) << "main loog thread exit";
  }));
}

void PulseAudioManager::Stop() {
  LOG(WARNING) << "pulseaudio stop";
  if (context_) {
    pa_context_disconnect(context_);
    pa_context_unref(context_);
  }

  if (mainloop_) {
    pa_mainloop_quit(mainloop_, 0);
    pa_mainloop_free(mainloop_);
  }

  if ((loop_thread_ != nullptr) && loop_thread_->joinable()) {
    loop_thread_->join();
    loop_thread_ = nullptr;
  }
}

void PulseAudioManager::ExitLoop() {
  LOG(WARNING) << "exit main loop";
  context_is_connect_ = false;
  if (mainloop_) {
    pa_mainloop_quit(mainloop_, 0);
  }
}

void PulseAudioManager::Play(const std::string &task_id, const std::string &path, int volume) {
  DeleteExpiredAudioStreamsHandle();

  LOG(INFO) << task_id << "," << path << "," << volume;
  if (!context_is_connect_) {
    LOG(ERROR) << "context is not ready";
    return;
  }

  auto audio_stream = std::make_shared<AudioStream>(task_id);
  if (audio_stream->Start(context_, path, volume)) {
    stream_manager_.Insert(std::make_pair(task_id, audio_stream));
    return;
  }
}

void PulseAudioManager::Pause() {
  LOG(WARNING) << "Pause all audio";
  stream_manager_.ForEach([](const std::string &, const std::shared_ptr<AudioStream> &stream) { stream->Pause(); });
}

void PulseAudioManager::Pause(const std::string &task_id) {
  LOG(WARNING) << "Pause audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.GetMutex());
  if (stream_manager_.IsExist(task_id)) {
    stream_manager_[task_id]->Pause();
  }
}

void PulseAudioManager::Resume() {
  LOG(WARNING) << "Resume all audio";
  stream_manager_.ForEach([](const std::string &, const std::shared_ptr<AudioStream> &stream) { stream->Resume(); });
}

void PulseAudioManager::Resume(const std::string &task_id) {
  LOG(WARNING) << "Resume audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.GetMutex());
  if (stream_manager_.IsExist(task_id)) {
    stream_manager_[task_id]->Resume();
  }
}

void PulseAudioManager::Cancel() {
  LOG(WARNING) << "Cancel all audio";
  stream_manager_.ForEach([](const std::string &, const std::shared_ptr<AudioStream> &stream) { stream->Cancel(); });
}

void PulseAudioManager::Cancel(const std::string &task_id) {
  LOG(WARNING) << "Cancel audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.GetMutex());
  if (stream_manager_.IsExist(task_id)) {
    stream_manager_[task_id]->Cancel();
  }
}

void PulseAudioManager::context_state_callback(pa_context *c, void *userdata) {
  auto *thiz = reinterpret_cast<PulseAudioManager *>(userdata);
  switch (pa_context_get_state(c)) {
    case PA_CONTEXT_READY: {
      thiz->context_is_connect_ = true;
      LOG(WARNING) << "context statue ready";
      break;
    }
    case PA_CONTEXT_FAILED:
    case PA_CONTEXT_TERMINATED:
    default:thiz->context_is_connect_ = false;
      LOG(ERROR) << "Context statue:" << pa_strerror(pa_context_errno(c));
      break;
  }
}

void PulseAudioManager::DeleteExpiredAudioStreamsHandle() {
  stream_manager_.RemoveIf([](const auto &elem) { return !elem.second->IsRunning(); });
}

}  // namespace enckit
}  // namespace kviolet
