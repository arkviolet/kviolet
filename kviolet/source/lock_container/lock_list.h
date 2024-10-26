#ifndef __KVIOLET__LOCK__LIST__H__
#define __KVIOLET__LOCK__LIST__H__

#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>

namespace kviolet {
namespace container {

template <class _Tp>
class LockList : public std::list<_Tp> {
 public:
  void PushBack(_Tp&& value) {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    std::list<_Tp>::push_back(std::forward<_Tp>(value));
    _condition.notify_all();
  }

  void PushBack(const _Tp& value) {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    std::list<_Tp>::push_back(value);

    _condition.notify_all();
  }

  void EmplaceBack(const _Tp& value) {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    std::list<_Tp>::emplace_back(value);
    _condition.notify_all();
  }

  std::size_t Size() {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    return std::list<_Tp>::size();
  }

  void Clear() {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    std::list<_Tp>::clear();
  }

  bool Empty() {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    return std::list<_Tp>::empty();
  }

  _Tp& Front() {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    return std::list<_Tp>::front();
  }

  void PopFront() {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    std::list<_Tp>::pop_front();
  }

  void WaitPopFront(_Tp& value) {
    std::unique_lock<std::recursive_mutex> lock(_mutex);
    _condition.wait(lock, [this] { return !std::list<_Tp>::empty(); });

    value = std::move(std::list<_Tp>::front());
    std::list<_Tp>::pop_front();
  }

  bool WaitPopFront(_Tp& value, uint64_t timeout) {
    std::unique_lock<std::recursive_mutex> lock(_mutex);

    if (0 == std::list<_Tp>::size() &&
        std::cv_status::timeout == _condition.wait_for(lock, std::chrono::milliseconds(timeout))) {
      return false;
    }

    value = std::move(std::list<_Tp>::front());
    std::list<_Tp>::pop_front();

    return true;
  }

  void Remove(const _Tp& value) {
    std::unique_lock<std::recursive_mutex> lock(_mutex);
    std::list<_Tp>::remove(value);  /// 顺序遍历查找删除
  }

  template <typename _Pre>
  void Remove(_Pre pr) {
    std::unique_lock<std::recursive_mutex> lock(_mutex);
    std::list<_Tp>::remove_if(pr);  /// 顺序遍历根据传入条件判断
  }

  void ForEach(const std::function<void(const _Tp& value)> cb) {
    std::unique_lock<std::recursive_mutex> lock(_mutex);
    for (auto& iter : *this) {  // TODO
      cb(iter);
    }
  }

  std::recursive_mutex* GetMutex() { return &_mutex; }

 private:
  std::recursive_mutex _mutex;
  std::condition_variable_any _condition;
};

}  // namespace container
}  // namespace kviolet

#endif  // __KVIOLET__LOCK__LIST__H__
