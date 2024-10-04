#ifndef __KVIOLET__LOCK__LIST__
#define __KVIOLET__LOCK__LIST__

#include <condition_variable>
#include <functional>
#include <list>
#include <mutex>

namespace kviolet {
namespace container {
template <class Type, class _Alloc = std::allocator<Type>>
class LockList : public std::list<Type, _Alloc> {
 public:
  template <class _Valty>
  void PushBack(_Valty&& value) {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    std::list<Type, _Alloc>::push_back(std::forward<_Valty>(value));
    cv_.notify_all();
  }

  template <class _Valty>
  void EmplaceBack(_Valty&& value) {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    std::list<Type, _Alloc>::emplace_back(std::forward<Type>(value));
    cv_.notify_all();
  }

  Type& Front() {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    return std::list<Type, _Alloc>::front();
  }

  bool Empty() {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    return std::list<Type, _Alloc>::empty();
  }

  void PopFront() {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    std::list<Type, _Alloc>::pop_front();
  }

  bool TryPopFront(const uint64_t timeout, Type& value) {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    if (std::list<Type, _Alloc>::size() == 0) {
      if (cv_.wait_for(lk, std::chrono::milliseconds(timeout)) == std::cv_status::timeout) {
        return false;
      }
    }

    value = std::list<Type, _Alloc>::front();
    std::list<Type, _Alloc>::pop_front();

    return true;
  }

  template <class _Pr1>
  auto RemoveIf(_Pr1 _Pred) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return std::list<Type, _Alloc>::remove_if(_Pred);
  }

  size_t Size() const {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return std::list<Type, _Alloc>::size();
  }

  void Clear() {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    std::list<Type, _Alloc>::clear();
  }

  void ForEach(const std::function<void(const Type&)>& callback) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    for (const auto& iter : *this) {
      callback(iter);
    }
  }

  std::recursive_mutex* GetMutex() { return &mutex_; }

 private:
  std::condition_variable_any cv_;
  mutable std::recursive_mutex mutex_;
};

}  // namespace container
}  // namespace kviolet

#endif  //__KVIOLET__LOCK__LIST__