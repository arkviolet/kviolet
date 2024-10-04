#include "builder_base.h"

namespace kviolet {
namespace kmessage {

MessageBuilderBase::MessageBuilderBase(const std::string& name) : name_(name) {};

std::shared_ptr<MessageBuilderBase> MessageBuilderBase::RegisterHandler(const std::shared_ptr<IHandler>& handler) {
  handlers_.push_back(handler);
  return shared_from_this();
}

std::shared_ptr<MessageBuilderBase> MessageBuilderBase::UnregisterHandler(const std::shared_ptr<IHandler>& handler) {
  handlers_.remove_if([&handler](const std::shared_ptr<IHandler>& h) { return h == handler; });
  return shared_from_this();
}

std::shared_ptr<MessageBuilderBase> MessageBuilderBase::UnregisterAllHandlers() {
  handlers_.clear();
  return shared_from_this();
}

void MessageBuilderBase::Run(const std::shared_ptr<ThreadPool>& thread_pool, const std::shared_ptr<Message>& message) {
  handlers_.ForEach([&](auto handler) { OnHandler(thread_pool, handler, message); });
}

std::shared_ptr<MessageBuilderBase> MessageBuilderBase::operator+=(const std::shared_ptr<IHandler>& handler) noexcept {
  return RegisterHandler(handler);
}

std::shared_ptr<MessageBuilderBase> MessageBuilderBase::operator-=(const std::shared_ptr<IHandler>& handler) noexcept {
  return UnregisterHandler(handler);
}

void MessageBuilderBase::OnHandler(const std::shared_ptr<ThreadPool>& thread_pool, const std::shared_ptr<IHandler>& handler, const std::shared_ptr<Message>& message) {
  handler->RunInner(message);
}

}  // namespace kmessage
}  // namespace kviolet
