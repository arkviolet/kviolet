#include "builder.h"

#include "looper.h"
#include "message.h"

namespace kviolet {
namespace message_queue {

std::shared_ptr<Message> Builder::Build() {
  auto message = std::make_shared<Message>();
  message->SetBuilder(shared_from_this());
  return message;
}

bool Builder::Send(const std::shared_ptr<Message> &message) {
  return Looper::MainLooper()->EnqueueMessage(message);
}

}  // namespace message_queue
}  // namespace kviolet
