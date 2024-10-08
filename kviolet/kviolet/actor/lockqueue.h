#ifndef __ACTOR__LOCK__QUEUE__H__
#define __ACTOR__LOCK__QUEUE__H__

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

namespace kviolet {
namespace actor {

template <typename TypeT>
class LockCQueue {
 public:
  LockCQueue(uint32_t size = 1024) { _maxSize = size; };

  ~LockCQueue() = default;

 public:
  void Push(TypeT&& value) {
    std::lock_guard<std::mutex> lock(_mutex);

    if (_queue.size() > _maxSize) {
      _queue.pop();

      std::cerr << "_queue.size:" << _maxSize << std::endl;
    }
    _queue.push(std::forward<TypeT>(value));

    _condition.notify_one();
  }

  void Push(const TypeT& value) {
    std::lock_guard<std::mutex> lock(_mutex);

    if (_queue.size() > _maxSize) {
      _queue.pop();

      std::cerr << "_queue.size:" << _maxSize << std::endl;
    }

    _queue.push(value);

    _condition.notify_one();
  }

  void Pop() {
    std::lock_guard<std::mutex> lock(_mutex);

    _queue.pop();
  }

  void Pop(TypeT& value) {
    std::lock_guard<std::mutex> lock(_mutex);

    value = std::move(_queue.front());

    _queue.pop();
  }

  void WaitAndPop() {
    std::unique_lock<std::mutex> lock(_mutex);

    _condition.wait(lock, [this] { return !_queue.empty(); });
    _queue.pop();
  }

  void WaiAndPop(TypeT& value) {
    std::unique_lock<std::mutex> lock(_mutex);

    _condition.wait(lock, [this] { return !_queue.empty(); });
    value = std::move(_queue.front());
    _queue.pop();
  }

  bool TryPop() {
    std::lock_guard<std::mutex> lock(_mutex);

    if (_queue.empty()) {
      return false;
    }

    _queue.pop();

    return true;
  }

  bool TryPop(TypeT& value) {
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

  const TypeT& Back() const {
    std::lock_guard<std::mutex> lock(_mutex);

    return _queue.back();
  }

  const TypeT& Front() const {
    std::lock_guard<std::mutex> lock(_mutex);

    return _queue.front();
  }

 private:
  uint32_t _maxSize;
  std::mutex _mutex{};
  std::queue<TypeT> _queue{};
  std::condition_variable _condition{};
};

}  // namespace actor
}  // namespace kviolet

#endif  ///__ACTOR__LOCK__QUEUE__H__
