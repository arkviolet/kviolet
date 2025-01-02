#include "looper.h"

#include "builder.h"

namespace kviolet {
namespace message_queue {

static std::mutex main_looper_mutex_;
static std::shared_ptr<Looper> main_looper_;

Looper::Ptr Looper::MainLooper() {
  std::lock_guard<std::mutex> lock(main_looper_mutex_);
  if (nullptr == main_looper_) {
    main_looper_ = std::make_shared<Looper>();
  }

  return main_looper_;
}

void Looper::StopMainLooper() {
  std::lock_guard<std::mutex> lock(main_looper_mutex_);
  main_looper_ = nullptr;
}

Looper::Looper() {
  _running = true;
  _work_thread = std::make_shared<std::thread>([this]() { Loop(); });
}

Looper::~Looper() {
  _running = false;
  if (_work_thread->joinable()) {
    _work_thread->join();
  }
}

void Looper::Exit() { _running = false; }

void Looper::Loop() {
  while (_running) {
    auto msg = _message_queue.Next();
    msg->Run();
  }
}

bool Looper::EnqueueMessage(const std::shared_ptr<Message>& message) {
  return _message_queue.Enqueue(message);
}

bool Looper::PostHandler(std::function<void(const std::shared_ptr<Message>&)> cb) {
  auto builder = std::make_shared<Builder>();

  builder->RegisterHandler(std::make_shared<Handler>(cb));

  return EnqueueMessage(builder->Build());
}

}  // namespace message_queue
}  // namespace kviolet