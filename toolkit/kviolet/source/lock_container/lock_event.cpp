#include "lock_event.h"

namespace kviolet {
namespace container {

void LockEvent::Notify(bool notify_all) noexcept {
  std::unique_lock<std::mutex> lock(_mutex);
  notify_all ? _condition.notify_all() : _condition.notify_one();
}

void LockEvent::Join() {
  std::unique_lock<std::mutex> lock(_mutex);
  _condition.wait(lock);
}

bool LockEvent::Join(uint64_t timeout) {
  std::unique_lock<std::mutex> lock(_mutex);
  return std::cv_status::timeout != _condition.wait_for(lock, std::chrono::milliseconds(timeout));
}

}  // namespace container
}  // namespace kviolet
