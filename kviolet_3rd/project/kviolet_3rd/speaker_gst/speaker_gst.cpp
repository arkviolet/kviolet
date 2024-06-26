#include "speaker_gst.h"

#include <glib.h>
#include <glog/logging.h>
#include <gst/gst.h>

#include <cmath>

namespace kviolet {

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
  bool Initialization(const std::string &taskid, const std::string &uri,
                      int volume) {
    launch_desc_ = g_strdup_printf("playbin uri=%s volume=%.3f", uri.c_str(),
                                   ConvertVolume((double)volume / 100));
    LOG(INFO) << "pipeline = " << launch_desc_;

    pipeline_ = gst_parse_launch(launch_desc_, &error_);
    if (nullptr == pipeline_) {
      LOG(ERROR) << "Failed to parse launch:" << error_->message;
      return false;
    }

    taskid_ = taskid;
    return true;
  }

  bool Play() {
    if (!pipeline_) {
      LOG(ERROR) << "pipeline is error";
      return false;
    }

    if (GST_STATE_CHANGE_FAILURE ==
        gst_element_set_state(pipeline_, GST_STATE_PLAYING)) {
      LOG(ERROR) << "play is error";
      return false;
    }

    bus_ = gst_element_get_bus(pipeline_);
    if (nullptr == bus_) {
      LOG(ERROR) << "bus is error";
      return false;
    }

    is_running_ = true;
    bus_thread_ = std::make_shared<std::thread>([this]() {
      while (is_running_) {
        auto msg = gst_bus_timed_pop_filtered(
            this->bus_, 1000 * GST_MSECOND,
            static_cast<GstMessageType>(GST_MESSAGE_STATE_CHANGED |
                                        GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

        if (nullptr == msg) {
          continue;
        }

        switch (GST_MESSAGE_TYPE(msg)) {
          case GST_MESSAGE_ERROR:
            gchar *debug_info;
            gst_message_parse_error(msg, &error_, &debug_info);
            LOG(ERROR) << "taskid:" << taskid_
                       << ":error received from element:" << error_->message;
            g_free(debug_info);
            is_running_ = false;
            break;
          case GST_MESSAGE_EOS:
            LOG(INFO) << "taskid:" << taskid_ << ":end-of-stream reached";
            is_running_ = false;
            break;
          case GST_MESSAGE_STATE_CHANGED:
            if (g_str_has_prefix(GST_MESSAGE_SRC_NAME(msg), "playbin")) {
              GstState old_state, new_state, pending_state;
              gst_message_parse_state_changed(msg, &old_state, &new_state,
                                              &pending_state);
              LOG(WARNING) << "taskid:" << taskid_ << ":"
                           << gst_element_state_get_name(old_state) << " to "
                           << gst_element_state_get_name(new_state);
            }
            break;
          default:
            LOG(ERROR) << "Unexpected message received.";
            break;
        }

        gst_message_unref(msg);
      }
      gst_element_set_state(pipeline_, GST_STATE_NULL);
      LOG(ERROR) << "taskid:" << taskid_ << ":play thread quit";
    });

    return true;
  }

  void Pause() {
    auto is_failure = GST_STATE_CHANGE_FAILURE ==
                      gst_element_set_state(pipeline_, GST_STATE_PAUSED);
    LOG(ERROR) << "taskid:" << taskid_ << ":pause status:" << is_failure;
  }

  void Resume() {
    auto is_failure = GST_STATE_CHANGE_FAILURE ==
                      gst_element_set_state(pipeline_, GST_STATE_PLAYING);
    LOG(ERROR) << "taskid:" << taskid_ << ":resume status:" << is_failure;
  }

  void Cancel() {
    is_running_ = false;
    auto is_failure = GST_STATE_CHANGE_FAILURE ==
                      gst_element_set_state(pipeline_, GST_STATE_NULL);
    LOG(ERROR) << "taskid:" << taskid_ << ":cancel status:" << is_failure;
  }

  bool IsRunning() { return is_running_; }

 protected:
  void Close() {
    if (bus_thread_ && bus_thread_->joinable()) {
      bus_thread_->join();
      bus_thread_ = nullptr;
    }

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
  std::shared_ptr<std::thread> bus_thread_{nullptr};
};

void GstAudioManager::Start() { gst_init(nullptr, nullptr); }

void GstAudioManager::Stop() { gst_deinit(); }

void GstAudioManager::Play(const std::string &task_id, const std::string &path,
                           int volume) {
  DeleteExpiredAudioStreamsHandle();

  LOG(INFO) << task_id << "," << path << "," << volume;

  auto audio_stream = std::make_shared<GstAudio>();

  if (!(audio_stream->Initialization(task_id, path, volume) &&
        audio_stream->Play())) {
    LOG(ERROR) << "gst stream error";
    return;
  }
  stream_manager_.insert(std::make_pair(task_id, audio_stream));
}

void GstAudioManager::Pause() {
  LOG(INFO) << "Pause all audio";
  stream_manager_.for_each(
      [](const std::string &, const std::shared_ptr<GstAudio> &stream) {
        stream->Pause();
      });
}

void GstAudioManager::Pause(const std::string &task_id) {
  LOG(INFO) << "Pause audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.get_mutex());
  if (stream_manager_.contains(task_id)) {
    stream_manager_[task_id]->Pause();
  }
}

void GstAudioManager::Resume() {
  LOG(INFO) << "Resume all audio";
  stream_manager_.for_each(
      [](const std::string &, const std::shared_ptr<GstAudio> &stream) {
        stream->Resume();
      });
}

void GstAudioManager::Resume(const std::string &task_id) {
  LOG(INFO) << "Resume audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.get_mutex());
  if (stream_manager_.contains(task_id)) {
    stream_manager_[task_id]->Resume();
  }
}

void GstAudioManager::Cancel() {
  LOG(INFO) << "Cancel all audio";
  stream_manager_.for_each(
      [](const std::string &, const std::shared_ptr<GstAudio> &stream) {
        stream->Cancel();
      });
}

void GstAudioManager::Cancel(const std::string &task_id) {
  LOG(INFO) << "Cancel audio:" << task_id;
  std::lock_guard<std::recursive_mutex> lk(*stream_manager_.get_mutex());
  if (stream_manager_.contains(task_id)) {
    stream_manager_[task_id]->Cancel();
  }
}

void GstAudioManager::DeleteExpiredAudioStreamsHandle() {
  stream_manager_.remove_if(
      [](const auto &elem) { return !elem.second->IsRunning(); });
}

}  // namespace kviolet
