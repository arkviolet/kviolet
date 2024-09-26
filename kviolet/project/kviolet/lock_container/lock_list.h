#ifndef __KVIOLET__LOCK__LIST__
#define __KVIOLET__LOCK__LIST__

#include <condition_variable>
#include <functional>
#include <list>
#include <mutex>

namespace kviolet {

template <class _Ty, class _Alloc = std::allocator<_Ty>>
class ConcurrentList : public std::list<_Ty, _Alloc> {
 public:
  template <class _Valty>
  void push_back(_Valty&& value) noexcept {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    std::list<_Ty, _Alloc>::push_back(std::forward<_Valty>(value));
    cv_.notify_all();
  }

  template <class _Valty>
  void emplace_back(_Valty&& value) noexcept {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    std::list<_Ty, _Alloc>::emplace_back(std::forward<_Ty>(value));
    cv_.notify_all();
  }

  _Ty& front() noexcept {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    return std::list<_Ty, _Alloc>::front();
  }

  bool empty() noexcept {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    return std::list<_Ty, _Alloc>::empty();
  }

  void pop_front() noexcept {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    std::list<_Ty, _Alloc>::pop_front();
  }

  bool try_pop_front(const uint64_t timeout, _Ty& value) {
    std::unique_lock<std::recursive_mutex> lk(mutex_);
    if (std::list<_Ty, _Alloc>::size() == 0) {
      if (cv_.wait_for(lk, std::chrono::milliseconds(timeout)) ==
          std::cv_status::timeout) {
        return false;
      }
    }

    value = std::list<_Ty, _Alloc>::front();
    std::list<_Ty, _Alloc>::pop_front();

    return true;
  }

  template <class _Pr1>
  auto remove_if(_Pr1 _Pred) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return std::list<_Ty, _Alloc>::remove_if(_Pred);
  }

  size_t size() const noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return std::list<_Ty, _Alloc>::size();
  }

  void clear() noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    std::list<_Ty, _Alloc>::clear();
  }

  void for_each(const std::function<void(const _Ty&)>& callback) noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    for (const auto& iter : *this) {
      callback(iter);
    }
  }

  std::recursive_mutex* get_mutex() noexcept { return &mutex_; }

 private:
  mutable std::recursive_mutex mutex_;
  std::condition_variable_any cv_;
};

}  // namespace kviolet

#endif  //__KVIOLET__LOCK__LIST__