#include "speaker_gst.h"

#include <glib.h>
#include <glog/logging.h>
#include <gst/gst.h>

#include <cmath>

namespace kviolet {
namespace enckit {

static double ConvertVolume(double volume) {
  if (volume <= 0.01) {
    return 0;
  }
  return pow(10, 2.1 * (volume - 1));
}

class GstAudio {
 public:
  ~GstAudio() { Close(); }

 public:
  bool Play(const std::string &taskid, const std::string &uri, int volume) {
    launch_desc_ = g_strdup_printf("playbin uri=%s volume=%.3f", uri.c_str(), ConvertVolume((double) volume / 100));

    LOG(INFO) << "pipeline = " << launch_desc_;
    if (nullptr == (pipeline_ = gst_parse_launch(launch_desc_, &error_))) {
      LOG(ERROR) << "Failed to parse launch:" << error_->message;
      return false;
    }

    if (GST_STATE_CHANGE_FAILURE == gst_element_set_state(pipeline_, GST_STATE_PLAYING)) {
      LOG(ERROR) << "playing uri error";
      return false;
    }

    if (nullptr == (bus_ = gst_element_get_bus(pipeline_))) {
      LOG(ERROR) << "bus is error";
      return false;
    }

    taskid_ = taskid;
    is_running_ = true;

    return true;
  }

  void Print() {
    while (is_running_) {
      auto msg = gst_bus_timed_pop_filtered(bus_,
                                            0 * GST_MSECOND,
                                            static_cast<GstMessageType>(GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR
                                                | GST_MESSAGE_EOS));
      if (nullptr == msg) {
        return;
      }

      if (GST_MESSAGE_STATE_CHANGED == GST_MESSAGE_TYPE(msg)) {
        if (g_str_has_prefix(GST_MESSAGE_SRC_NAME(msg), "playbin")) {
          GstState state;
          gst_message_parse_state_changed(msg, nullptr, &state, nullptr);
          LOG(INFO) << taskid_ << "," << gst_element_state_get_name(state);
        }
      } else {
        is_running_ = false;
        gst_element_set_state(pipeline_, GST_STATE_NULL);
        if (GST_MESSAGE_EOS == GST_MESSAGE_TYPE(msg)) {
          LOG(INFO) << taskid_ << " end-of-stream ";
        } else {
          gchar *debug_info;
          gst_message_parse_error(msg, &error_, &debug_info);
          LOG(ERROR) << taskid_ << ",error received" << error_->message;
          g_free(debug_info);
        }
      }

      gst_message_unref(msg);
    }
  }

  void Pause() {
    LOG(INFO) << taskid_ << ",pause";
    gst_element_set_state(pipeline_, GST_STATE_PAUSED);
  }

  void Resume() {
    LOG(INFO) << taskid_ << ",resume";
    gst_element_set_state(pipeline_, GST_STATE_PLAYING);
  }

  void Cancel() {
    is_running_ = false;
    LOG(INFO) << taskid_ << ",cancel";
    gst_element_set_state(pipeline_, GST_STATE_NULL);
  }

  bool IsRunning() { return is_running_; }

 protected:
  void Close() {
    LOG(INFO) << taskid_ << ",close";

    if (launch_desc_) {
      g_free(launch_desc_);
      launch_desc_ = nullptr;
    }
    if (error_) {
      g_error_free(error_);
      error_ = nullptr;
    }

    if (pipeline_) {
      gst_object_unref(pipeline_);
      pipeline_ = nullptr;
    }

    if (bus_) {
      gst_object_unref(bus_);
      bus_ = nullptr;
    }
  }

 private:
  bool is_running_{false};
  std::string taskid_{""};
  char *launch_desc_{nullptr};
  GstBus *bus_{nullptr};
  GError *error_{nullptr};
  GstElement *pipeline_{nullptr};
};

void GstAudioManager::Start() {
  is_running_ = true;

  gst_init(nullptr, nullptr);

  listener_thread_ = std::make_shared<std::thread>([this]() { Listener(); });
}

void GstAudioManager::Stop() {
  is_running_ = false;

  if (listener_thread_->joinable()) {
    listener_thread_->join();
  }

  gst_deinit();
}

void GstAudioManager::Play(const std::string &task_id, const std::string &path, int volume) {
  auto audio_stream = std::make_shared<GstAudio>();
  if (audio_stream->Play(task_id, path, volume)) {
    stream_manager_.Insert(std::make_pair(task_id, audio_stream));
  }
}

void GstAudioManager::Pause() {
  LOG(WARNING) << "Pause all audio";
  stream_manager_.ForEach([](const std::string &, const std::shared_ptr<GstAudio> &stream) { stream->Pause(); });
}

void GstAudioManager::Pause(const std::string &task_id) {
  LOG(WARNING) << "Pause audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.GetMutex());
  if (stream_manager_.IsExist(task_id)) {
    stream_manager_[task_id]->Pause();
  }
}

void GstAudioManager::Resume() {
  LOG(WARNING) << "Resume all audio";
  stream_manager_.ForEach([](const std::string &, const std::shared_ptr<GstAudio> &stream) { stream->Resume(); });
}

void GstAudioManager::Resume(const std::string &task_id) {
  LOG(WARNING) << "Resume audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.GetMutex());
  if (stream_manager_.IsExist(task_id)) {
    stream_manager_[task_id]->Resume();
  }
}

void GstAudioManager::Cancel() {
  LOG(WARNING) << "Cancel all audio";
  stream_manager_.ForEach([](const std::string &, const std::shared_ptr<GstAudio> &stream) { stream->Cancel(); });
}

void GstAudioManager::Cancel(const std::string &task_id) {
  LOG(WARNING) << "Cancel audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.GetMutex());
  if (stream_manager_.IsExist(task_id)) {
    stream_manager_[task_id]->Cancel();
  }
}

void GstAudioManager::Listener() {
  do {
    stream_manager_.ForEach([](const std::string &, const std::shared_ptr<GstAudio> &stream) { stream->Print(); });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    DeleteExpiredAudioStreamsHandle();

  } while (is_running_);
}

void GstAudioManager::DeleteExpiredAudioStreamsHandle() {
  stream_manager_.RemoveIf([](const auto &elem) { return !elem.second->IsRunning(); });
}

}  // namespace enckit
}  // namespace kviolet
