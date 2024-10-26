#ifndef __KVIOLET__MESSAGE__QUEUE__LOOPER__H__
#define __KVIOLET__MESSAGE__QUEUE__LOOPER__H__

#include <thread>

#include "message.h"
#include "message_queue.h"

namespace kviolet {
namespace message_queue {

class Looper {
 public:
  using Ptr = std::shared_ptr<Looper>;

 public:
  static Ptr MainLooper();
  static void StopMainLooper();

 public:
  explicit Looper();
  ~Looper();

 public:
  void Exit();

  void Loop();

  bool EnqueueMessage(const std::shared_ptr<Message>& message);

  bool PostHandler(std::function<void(const std::shared_ptr<Message>&)> handler);

 private:
  bool _running;
  MessageQueue _message_queue;
  std::shared_ptr<std::thread> _work_thread;
};

}  // namespace message_queue
}  // namespace kviolet

#endif  //__KVIOLET__MESSAGE__QUEUE__LOOPER__H__