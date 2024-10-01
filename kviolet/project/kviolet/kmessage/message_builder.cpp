#include "message_builder.h"

namespace kviolet {
namespace kmessage {

MessageBuilder::MessageBuilder() : looper_(Looper::GetMainLooper()) {}

MessageBuilder::MessageBuilder(const std::string& name) : MessageBuilderBase(name), looper_(Looper::GetMainLooper()) {}

MessageBuilder::MessageBuilder(const std::shared_ptr<Looper>& looper) : looper_(looper) {}

MessageBuilder::MessageBuilder(const std::string& name, const std::shared_ptr<Looper>& looper) : MessageBuilderBase(name), looper_(looper) {}

std::shared_ptr<MessageBuilderBase> MessageBuilder::RegisterHandler(const typename FunctionHandler::Callback& callback) {
  return MessageBuilderBase::RegisterHandler(std::make_shared<FunctionHandler>(callback));
}

std::shared_ptr<Message> MessageBuilder::Build() {
  auto message = std::make_shared<Message>();
  message->SetBuilder(shared_from_this());
  return message;
}

bool MessageBuilder::Send(const std::shared_ptr<Message>& message, const uint64_t when) {
  return looper_->EnqueueMessage(message, when);
}

bool MessageBuilder::Invoke(const std::shared_ptr<Message>& message, const uint64_t when, const int64_t timeout_ms) {
  if (looper_->EnqueueMessage(message, when)) {
    return message->Join(timeout_ms);
  } else {
    return false;
  }
}

bool AsyncMessageBuilder::Invoke(const std::shared_ptr<Message>& message, const uint64_t when, const int64_t timeout_ms) {
  return false;
}

void AsyncMessageBuilder::OnHandler(const std::shared_ptr<ThreadPool>& pool, const std::shared_ptr<IHandler>& handler, const std::shared_ptr<Message>& message) {
  pool->Commit([handler, message]() { handler->RunInner(message); });
}

}  // namespace kmessage
}  // namespace kviolet
