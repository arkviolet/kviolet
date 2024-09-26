#ifndef __KVIOLET__MESSAGE_QUEUE__H__
#define __KVIOLET__MESSAGE_QUEUE__H__

#include <iostream>

#include "../lock_container/lock_event.h"
#include "../lock_container/lock_list.h"
#include "message.h"

namespace kviolet {

class MessageQueue {
 public:
  MessageQueue() = default;
  virtual ~MessageQueue() { Quit(); }

 public:
  std::shared_ptr<Message> Next();

  bool EnqueueMessage(const std::shared_ptr<Message> &message,
                      uint64_t when = 0);

  void Clean();
  void Quit();
  void Dump();

 private:
  bool quit_{false};
  LockEvent event_;
  ConcurrentList<std::shared_ptr<Message>> list_;
};

}  // namespace kviolet

#endif  ///__KVIOLET__MESSAGE_QUEUE__H__
