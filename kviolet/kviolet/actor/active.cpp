#include "active.h"

#include "event.h"
#include "handle.h"

namespace kviolet {
namespace actor {

Active::Active(PseudoState init, const std::shared_ptr<Handle>& handle)
    : Hsm(init), _running(true), _handle(handle) {}

Active::~Active() { Stop(); }

void Active::Start() {
  _running = true;
  _work_thread = std::make_shared<std::thread>([this]() {
    while (_running) {
      auto event = _queue.Pop();

      Dispatch(event);
    }
  });
}
void Active::Stop() {
  _running = false;

  if (!_queue.Size()) {
    _queue.PushBack(StdEventPtr[EVENT_EMPTY]);
  }

  if (_work_thread && _work_thread->joinable()) {
    _work_thread->join();
    _work_thread = nullptr;
  }
}

void Active::PushBack(const std::shared_ptr<Event>& event) { _queue.PushBack(event); }

void Active::PushFront(const std::shared_ptr<Event>& event) { _queue.PushFront(event); }

void Active::Subscribe(Signal event) { _handle->Subscribe(shared_from_this(), event); }

void Active::UnSubscribe(Signal event) { _handle->UnSubscribe(shared_from_this(), event); }

void Active::Publish(const std::shared_ptr<Event>& event) { _handle->Publish(event); }

}  // namespace actor
}  // namespace kviolet
