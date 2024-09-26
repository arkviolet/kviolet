#include "message.h"

namespace kviolet {

Message::Message(const std::shared_ptr<MessageBuilderBase>& builder)
    : builder_(builder) {}
Message::~Message() {}

void Message::SetBuilder(const std::shared_ptr<MessageBuilderBase>& builder) {
  builder_ = builder;
}

uint64_t Message::When() { return when_; }

void Message::SetWhen(const uint64_t when) { when_ = when; }

void Message::Join() { event_.Join(); }

bool Message::Join(const int64_t timeout_ms) { return event_.Join(timeout_ms); }

void Message::Notify() { event_.Notify(); }

void Message::Run(const std::shared_ptr<ThreadPool>& pool) {
  builder_->Run(pool, shared_from_this());
}

void Message::Send(const uint64_t when) {
  builder_->Send(shared_from_this(), when);
}

void Message::Invoke(const uint64_t when) {
  builder_->Invoke(shared_from_this(), when);
}
}  // namespace kviolet