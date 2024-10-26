#ifndef __KVIOLET__ENCKIT__SPEAKER__GST__H__
#define __KVIOLET__ENCKIT__SPEAKER__GST__H__

#include <memory>
#include <string>
#include <thread>

#include "kviolet/lock_container/lock_map.h"

namespace kviolet {
namespace enckit {

using namespace kviolet::container;

class GstAudio;

class GstAudioManager final {
 public:
  GstAudioManager() { Start(); }
  ~GstAudioManager() { Stop(); }

 protected:
  void Start();
  void Stop();

 public:
  void Play(const std::string &task_id, const std::string &path, int volume);
  void Pause();
  void Pause(const std::string &task_id);
  void Resume();
  void Resume(const std::string &task_id);
  void Cancel();
  void Cancel(const std::string &task_id);

 protected:
  void Listener();
  void DeleteExpiredAudioStreamsHandle();

 private:
  bool is_running_;
  std::shared_ptr<std::thread> listener_thread_;
  LockMap<std::string, std::shared_ptr<GstAudio>> stream_manager_;
};

}  // namespace enckit
}  // namespace kviolet

#endif  // __KVIOLET__ENCKIT__SPEAKER__GST__H__
