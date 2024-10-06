#include "message_queue.h"

#include <iostream>

namespace kviolet {
namespace message_queue {

bool MessageQueue::Enqueue(const std::shared_ptr<Message>& message) {
  _list.PushBack(message);
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