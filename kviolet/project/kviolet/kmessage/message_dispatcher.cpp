
#include "message_dispatcher.h"

#include "../lock_container/lock_map.h"

namespace kviolet {
namespace kmessage {

static LockMap<std::shared_ptr<Looper>, std::shared_ptr<MessageBuilder>> builders;

void MessageQueueDispatcher::RegisterHandler(Callback&& callback, const std::shared_ptr<Looper>& looper) {
  GetBuilder(looper)->RegisterHandler(std::forward<Callback>(callback));
}

void MessageQueueDispatcher::Send(const std::shared_ptr<Message>& message, const std::shared_ptr<Looper>& looper) {
  message->SetBuilder(GetBuilder(looper));
  message->Send();
}

std::shared_ptr<MessageBuilder> MessageQueueDispatcher::GetBuilder(const std::shared_ptr<Looper>& looper) {
  std::shared_ptr<MessageBuilder> builder;
  std::lock_guard lock(*builders.GetMutex());
  if (!builders.Find(looper, builder)) {
    if (looper) {
      auto new_builder = std::make_shared<MessageBuilder>(looper);
      builders.Insert(std::make_pair(looper, new_builder));
      return new_builder;
    } else {
      auto new_builder = std::make_shared<MessageBuilder>();
      builders.Insert(std::make_pair(looper, new_builder));
      return new_builder;
    }
  } else {
    return builder;
  }
}

}  // namespace kmessage
}  // namespace kviolet
