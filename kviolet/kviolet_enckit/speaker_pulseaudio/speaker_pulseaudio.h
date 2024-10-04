#ifndef __KVIOLET__3RD__SPEAKER__PULSEAUDIP____H__
#define __KVIOLET__3RD__SPEAKER__PULSEAUDIP____H__

#include <pulse/pulseaudio.h>

#include "../../kviolet/lock_container/lock_map.h"

#include <memory>
#include <string>
#include <thread>

namespace kviolet {
namespace enckit {

using namespace kviolet::container;

class AudioStream;

class PulseAudioManager final {
 public:
  PulseAudioManager() { Start(); }
  ~PulseAudioManager() { Stop(); }

 protected:
  void Start();
  void Stop();

 public:
  void ExitLoop();
  void Play(const std::string& task_id, const std::string& path, int volume);
  void Pause();
  void Pause(const std::string& task_id);
  void Resume();
  void Resume(const std::string& task_id);
  void Cancel();
  void Cancel(const std::string& task_id);

 protected:
  static void context_state_callback(pa_context* c, void* userdata);
  void DeleteExpiredAudioStreamsHandle();

 private:
  pa_context* context_{};
  pa_mainloop* mainloop_{};
  bool context_is_connect_{false};
  std::shared_ptr<std::thread> loop_thread_;
  LockMap<std::string, std::shared_ptr<AudioStream>> stream_manager_;
};

}  // namespace enckit
}  // namespace kviolet

#endif  // __KVIOLET__3RD__SPEAKER__PULSEAUDIP____H__
