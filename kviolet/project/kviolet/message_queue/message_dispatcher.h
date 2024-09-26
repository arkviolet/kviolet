#ifndef __KVIOLET__MESSAGE__DISPATCHER__H__
#define __KVIOLET__MESSAGE__DISPATCHER__H__

#include <functional>

#include "looper.h"
#include "message.h"
#include "message_builder.h"

namespace kviolet {

class MessageQueueDispatcher {
 public:
  using Callback = std::function<void(const std::shared_ptr<Message>&)>;

  static void RegisterHandler(Callback&& callback,
                              const std::shared_ptr<Looper>& looper = nullptr);

  static void Send(const std::shared_ptr<Message>& message,
                   const std::shared_ptr<Looper>& looper = nullptr);

  static std::shared_ptr<MessageBuilder> GetBuilder(
      const std::shared_ptr<Looper>& looper);
};

}  // namespace kviolet

#endif  ///__KVIOLET__MESSAGE__DISPATCHER__H__
