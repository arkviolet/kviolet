#include "speaker_pulseaudio.h"

#include <glog/logging.h>
#include <kviolet/utilities/timestamp.h>
#include <sndfile.h>

namespace kviolet {

class AudioStream {
 public:
  AudioStream(pa_stream *stream, const std::string &task_id);
  ~AudioStream();

 public:
  bool Start(const std::string &path);
  void Pause();
  void Resume();
  void Cancel();
  bool IsExpire(uint64_t current_time);

 protected:
  void Close();
  void SetExpireTime();
  static void stream_state_callback(pa_stream *s, void *userdata);
  static void stream_request_cb(pa_stream *s, size_t length, void *userdata);

 private:
  FILE *file_;
  uint64_t expire_time_;
  pa_stream *stream_;
  std::string task_id_;
  uint64_t index_{0};
};

AudioStream::AudioStream(pa_stream *stream, const std::string &task_id)
    : file_(nullptr), expire_time_{0}, stream_(stream), task_id_(task_id){};

AudioStream::~AudioStream() { Close(); }

std::string strstr;
bool AudioStream::Start(const std::string &path) {
  file_ = fopen(path.c_str(), "rb");
  if (!file_) {
    LOG(ERROR) << "open video file error:" << path;
    return false;
  }

  pa_stream_set_write_callback(stream_, stream_request_cb, this);
  pa_stream_set_state_callback(stream_, stream_state_callback, this);
  return true;
}

void AudioStream::Pause() {
  if (stream_) {
    pa_stream_cork(stream_, 1, nullptr, nullptr);
  }
}

void AudioStream::Resume() {
  if (stream_) {
    pa_stream_cork(stream_, 0, nullptr, nullptr);
  };
}

void AudioStream::Cancel() { Close(); };

bool AudioStream::IsExpire(uint64_t current_time) {
  if (expire_time_ && current_time - expire_time_ > 3) {
    return true;
  }
  return false;
}

void AudioStream::Close() {
  if (stream_) {
    pa_stream_set_write_callback(stream_, nullptr, nullptr);
    pa_stream_set_state_callback(stream_, nullptr, nullptr);
    pa_stream_disconnect(stream_);
    pa_stream_unref(stream_);
    stream_ = nullptr;
    LOG(INFO) << task_id_ << ",stream is close";
  }

  if (file_) {
    fclose(file_);
    file_ = nullptr;
  }

  SetExpireTime();
}

void AudioStream::SetExpireTime() {
  if (!expire_time_) {
    expire_time_ = timestamp::Timestamp::MonotonicSeconds();
  }
}

void AudioStream::stream_state_callback(pa_stream *s, void *userdata) {
  auto *thiz = reinterpret_cast<AudioStream *>(userdata);
  switch (pa_stream_get_state(s)) {
    case PA_STREAM_CREATING:
    case PA_STREAM_TERMINATED:
      break;
    case PA_STREAM_READY:
      LOG(INFO) << thiz->task_id_ << ",stream is ready";
      break;
    case PA_STREAM_FAILED:
    default:
      LOG(WARNING) << thiz->task_id_ << ",stream error:"
                   << pa_strerror(pa_context_errno(pa_stream_get_context(s)));
      break;
  }
}

void AudioStream::stream_request_cb(pa_stream *s, size_t length,
                                    void *userdata) {
  auto *thiz = reinterpret_cast<AudioStream *>(userdata);
  auto buffer = new (std::nothrow) uint8_t[length];
  if (!buffer) {
    LOG(ERROR) << thiz->task_id_ << ",new failed";
    thiz->SetExpireTime();
    return;
  }
  auto ret = fread(buffer, 1, length, thiz->file_);
  if (0 == ret ||
      0 != pa_stream_write(s, buffer, ret, nullptr, 0, PA_SEEK_RELATIVE)) {
    LOG(WARNING) << thiz->task_id_ << ",write stream done";
    thiz->SetExpireTime();
  }
  delete[] buffer;
}

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

void PulseAudioManager::Play(const std::string &task_id,
                             const std::string &path, int volume) {
  LOG(INFO) << task_id << "," << path << "," << volume;
  if (!context_is_connect_) {
    LOG(ERROR) << "context is not ready";
    return;
  }

  pa_cvolume cvolume;
  auto sample_spec = GetAudioFormat(path);
  pa_cvolume_set(&cvolume, sample_spec.channels,
                 (pa_volume_t)(((double)volume / 100) * PA_VOLUME_NORM));

  auto stream = pa_stream_new(context_, task_id.c_str(), &sample_spec, nullptr);
  if (!stream) {
    LOG(ERROR) << task_id
               << " pa_stream_new:" << pa_strerror(pa_context_errno(context_))
               << std::endl;
    return;
  }

  auto audio_stream = std::make_shared<AudioStream>(stream, task_id);
  if (audio_stream->Start(path) &&
      0 == pa_stream_connect_playback(stream, nullptr, NULL, PA_STREAM_NOFLAGS,
                                      &cvolume, nullptr)) {
    stream_manager_.insert(std::make_pair(task_id, audio_stream));
  }

  DeleteExpiredAudioStreamsHandle();
}

void PulseAudioManager::Pause() {
  LOG(WARNING) << "Pause all audio";
  stream_manager_.for_each(
      [](const std::string &, const std::shared_ptr<AudioStream> &stream) {
        stream->Pause();
      });
}

void PulseAudioManager::Pause(const std::string &task_id) {
  LOG(WARNING) << "Pause audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.get_mutex());
  if (stream_manager_.contains(task_id)) {
    stream_manager_[task_id]->Pause();
  }
}

void PulseAudioManager::Resume() {
  LOG(WARNING) << "Resume all audio";
  stream_manager_.for_each(
      [](const std::string &, const std::shared_ptr<AudioStream> &stream) {
        stream->Resume();
      });
}

void PulseAudioManager::Resume(const std::string &task_id) {
  LOG(WARNING) << "Resume audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.get_mutex());
  if (stream_manager_.contains(task_id)) {
    stream_manager_[task_id]->Resume();
  }
}

void PulseAudioManager::Cancel() {
  LOG(WARNING) << "Cancel all audio";
  stream_manager_.for_each(
      [](const std::string &, const std::shared_ptr<AudioStream> &stream) {
        stream->Cancel();
      });
}

void PulseAudioManager::Cancel(const std::string &task_id) {
  LOG(WARNING) << "Cancel audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.get_mutex());
  if (stream_manager_.contains(task_id)) {
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
    default:
      thiz->context_is_connect_ = false;
      LOG(ERROR) << "Context statue:" << pa_strerror(pa_context_errno(c));
      break;
  }
}

pa_sample_spec PulseAudioManager::GetAudioFormat(const std::string &path) {
  SF_INFO sfi;
  pa_sample_spec sample_spec = {PA_SAMPLE_S16LE, 44100, 2};
  auto *sf = sf_open(path.c_str(), SFM_READ, &sfi);
  if (!sf) {
    LOG(ERROR) << "sf_open error:" << sf_strerror(nullptr);
    return sample_spec;
  }
  sf_close(sf);
  switch (sfi.format & SF_FORMAT_SUBMASK) {
    case SF_FORMAT_PCM_16:
    case SF_FORMAT_PCM_U8:
    case SF_FORMAT_PCM_S8:
      sample_spec.format = PA_SAMPLE_S16NE;
      break;

    case SF_FORMAT_PCM_32:
    case SF_FORMAT_PCM_24:
      /* note that libsndfile will convert 24 bits samples to 32 bits
       * when using the sf_readf_int function, which will be selected
       * by setting the format to s32. */
      sample_spec.format = PA_SAMPLE_S32NE;
      break;

    case SF_FORMAT_ULAW:
      sample_spec.format = PA_SAMPLE_ULAW;
      break;

    case SF_FORMAT_ALAW:
      sample_spec.format = PA_SAMPLE_ALAW;
      break;

    case SF_FORMAT_FLOAT:
    case SF_FORMAT_DOUBLE:
    default:
      sample_spec.format = PA_SAMPLE_FLOAT32NE;
      break;
  }

  sample_spec.rate = (uint32_t)sfi.samplerate;
  sample_spec.channels = (uint8_t)sfi.channels;
  return sample_spec;
}

void PulseAudioManager::DeleteExpiredAudioStreamsHandle() {
  auto current_time = timestamp::Timestamp::MonotonicSeconds();
  stream_manager_.remove_if(
      [&](const auto &elem) { return elem.second->IsExpire(current_time); });
}
}  // namespace kviolet
