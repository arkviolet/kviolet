#ifndef __KVIOLET__MESSAGE__QUEUE__DISPATCHER__H__
#define __KVIOLET__MESSAGE__QUEUE__DISPATCHER__H__

#include "builder.h"
#include "handler.h"
#include "message.h"

namespace kviolet {
namespace message_queue {

class Dispatcher {
 public:
  static void RegisterHandler(const Handler::Callback& cb) {
    GetBuilder()->RegisterHandler(std::make_shared<Handler>(cb));
  }

  static void Send(const std::shared_ptr<Message>& message) {
    message->SetBuilder(GetBuilder());
    message->Send();
  }

  template <typename MessageType>
  static void Send(const std::shared_ptr<MessageType>& message) {
    std::shared_ptr<Message> msg = message;
    message->SetBuilder(GetBuilder());
    message->Send();
  }

  static Builder::Ptr GetBuilder() {
    static auto builder = std::make_shared<Builder>();
    return builder;
  }
};

}  // namespace message_queue
}  // namespace kviolet

#endif  //__KVIOLET__MESSAGE__QUEUE__DISPATCHER__H__