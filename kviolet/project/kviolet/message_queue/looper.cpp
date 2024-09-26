
#include "looper.h"

#include "message_builder.h"

namespace kviolet {
static std::shared_ptr<Looper> static_main_looper_;
static std::mutex static_main_looper_mutex_;

std::shared_ptr<Looper> Looper::GetMainLooper(bool auto_start) {
  std::lock_guard<std::mutex> lock(static_main_looper_mutex_);
  if (static_main_looper_ == nullptr) {
    static_main_looper_ = std::make_shared<Looper>("MainLooper", auto_start);
  }
  return static_main_looper_;
}

void Looper::StopMainLooper() {
  std::lock_guard<std::mutex> lock(static_main_looper_mutex_);
  static_main_looper_ = nullptr;
}

Looper::Looper(const std::string& name) {
  tid_ = std::this_thread::get_id();
  pool_ = std::make_shared<ThreadPool>();
}

Looper::Looper(const std::string& name, bool auto_start) {
  tid_ = std::this_thread::get_id();
  pool_ = std::make_shared<ThreadPool>();
  if (auto_start) {
    AsyncLoop();
  }
}

Looper::~Looper() { Exit(); }

void Looper::AsyncLoop() {
  thread_.reset(new std::thread([&]() {
    Loop();
    return false;
  }));
}

void Looper::Loop() {
  while (!quit_) {
    auto message = message_queue_.Next();
    if (message == nullptr) {
      return;
    }

    message->Run(pool_);
    message->Notify();
  }
}

void Looper::Exit() {
  quit_ = true;
  message_queue_.Quit();

  if (thread_ && thread_->joinable()) {
    thread_->join();
    thread_ = nullptr;
  }
}

bool Looper::EnqueueMessage(const std::shared_ptr<Message>& message,
                            const uint64_t when) {
  return message_queue_.EnqueueMessage(message, when);
}

bool Looper::PostHandler(const std::function<void()>& handler,
                         const uint64_t when) {
  auto builder = std::make_shared<MessageBuilder>();
  builder->RegisterHandler(
      [handler](const std::shared_ptr<Message>& message) { handler(); });
  return EnqueueMessage(builder->Build(), when);
}

}  // namespace kviolet
