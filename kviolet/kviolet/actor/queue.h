#ifndef __KVIOLET__ACTOR__QUEUE__H__
#define __KVIOLET__ACTOR__QUEUE__H__

#include <condition_variable>
#include <deque>
#include <mutex>

namespace kviolet {
namespace actor {

template <class Tp_>
class Deque {
 public:
  void PushBack(const Tp_& value) {
    std::lock_guard<std::mutex> lock(_mutex);
    _deque.push_back(value);
    _condition.notify_one();
  }

  void PushFront(const Tp_& value) {
    std::lock_guard<std::mutex> lock(_mutex);
    _deque.push_front(value);
    _condition.notify_one();
  }

  Tp_ Pop() {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_deque.empty()) {
      _condition.wait(lock, [this] { return !_deque.empty(); });
    }
    auto value = std::move(_deque.front());
    _deque.pop_front();
    return value;
  }

  std::size_t Size() {
    std::lock_guard<std::mutex> lock(_mutex);
    return _deque.size();
  }

 private:
  std::mutex _mutex;
  std::deque<Tp_> _deque;
  std::condition_variable _condition;
};

}  // namespace actor
}  // namespace kviolet

#endif  // __KVIOLET__ACTOR__QUEUE__H__