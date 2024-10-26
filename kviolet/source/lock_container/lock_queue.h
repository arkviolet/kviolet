#ifndef __KVIOLET__LOCK__QUEUE__H__
#define __KVIOLET__LOCK__QUEUE__H__

#include <condition_variable>
#include <mutex>
#include <queue>

namespace kviolet {
namespace container {

template<typename TypeT>
class LockQueue {
 public:
  void Push(TypeT &&value) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(std::forward<TypeT>(value));
    _condition.notify_all();
  }

  void Push(const TypeT &value) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(value);
    _condition.notify_all();
  }

  void Pop() {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.pop();
  }

  void Pop(TypeT &value) {
    std::lock_guard<std::mutex> lock(_mutex);
    value = std::move(_queue.front());
    _queue.pop();
  }

  void WaitAndPop() {
    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock, [this] { return !_queue.empty(); });
    _queue.pop();
  }

  void WaiAndPop(TypeT &value) {
    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock, [this] { return !_queue.empty(); });
    value = std::move(_queue.front());
    _queue.pop();
  }

  bool WaiAndPop(uint64_t timeout, TypeT &value) {
    std::unique_lock<std::mutex> lock(_mutex);

    if (0 == _queue.size()) {
      if (_condition.wait_for(lock, std::chrono::milliseconds(timeout)) == std::cv_status::timeout) {
        return false;
      }
    }

    value = std::move(_queue.front());
    _queue.pop();

    return true;
  }

  bool TryPop() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_queue.empty()) {
      return false;
    }
    _queue.pop();
    return true;
  }

  bool TryPop(TypeT &value) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_queue.empty()) {
      return false;
    }
    value = std::move(_queue.front());
    _queue.pop();

    return true;
  }

  bool Empty() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.empty();
  }

  std::size_t Size() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.size();
  }

  const TypeT &Back() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.back();
  }

  const TypeT &Front() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.front();
  }

 private:
  std::queue<TypeT> _queue{};
  mutable std::mutex _mutex{};
  std::condition_variable _condition{};
};

}  // namespace container
}  // namespace kviolet

#endif  ///__KVIOLET__LOCK__QUEUE__H__
