#ifndef __KVIOLET__MESSAGE__LOOPER__H__
#define __KVIOLET__MESSAGE__LOOPER__H__

#include <thread>

#include "../lock_container/lock_event.h"
#include "message.h"
#include "message_queue.h"

namespace kviolet {
class Looper {
 public:
  static std::shared_ptr<Looper> GetMainLooper(bool start = true);
  static void StopMainLooper();

 public:
  explicit Looper(const std::string& name);
  explicit Looper(const std::string& name, bool auto_start);
  virtual ~Looper();

 public:
  void AsyncLoop();
  void Loop();
  void Exit();
  bool EnqueueMessage(const std::shared_ptr<Message>& message,
                      const uint64_t when = 0);
  bool PostHandler(const std::function<void()>& handler,
                   const uint64_t when = 0);

 private:
  std::string name_;
  MessageQueue message_queue_;
  std::shared_ptr<ThreadPool> pool_;
  std::shared_ptr<std::thread> thread_;
  std::thread::id tid_;
  bool quit_{false};
};

}  // namespace kviolet

#endif  ///__KVIOLET__MESSAGE__LOOPER__H__
