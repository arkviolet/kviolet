#include "message_queue.h"

#include <iostream>

namespace kviolet {
namespace message_queue {

bool MessageQueue::Enqueue(const std::shared_ptr<Message>& message) {
  std::lock_guard<std::recursive_mutex> lk(*_list.GetMutex());

  uint32_t index = 0;
  auto when = message->When();

  decltype(_list)::iterator iter = _list.begin();
  for (; iter != _list.end(); ++iter) {
    if (iter->get()->When() > when) {
      break;
    }
  }
  _list.insert(iter, message);

  return true;
}

std::shared_ptr<Message> MessageQueue::Next() {
  std::shared_ptr<Message> message;
  _list.WaitPopFront(message);
  return message;
}

void MessageQueue::MessageQueue::Dump() {
  std::cout << "Dump" << std::endl;

  _list.ForEach([](const std::shared_ptr<Message>& message) {
    // TODO
  });

  std::cout << std::endl;
}

}  // namespace message_queue
}  // namespace kviolet