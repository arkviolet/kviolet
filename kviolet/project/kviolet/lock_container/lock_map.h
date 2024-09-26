#ifndef __KVIOLET__LOCK__MAP__
#define __KVIOLET__LOCK__MAP__

#include <functional>
#include <map>
#include <mutex>

namespace kviolet {

template <class _Kty, class _Ty, class _Pr = std::less<_Kty>,
          class _Alloc = std::allocator<std::pair<const _Kty, _Ty>>>
class ConcurrentMap {
 public:
  using key_type = _Kty;
  using mapped_type = _Ty;
  using value_type = std::pair<const _Kty, _Ty>;

 public:
  template <class _Valty>
  void insert(_Valty&& _Val) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    map_.insert(std::forward<_Valty>(_Val));
  }

  _Ty& operator[](const _Kty& _Key) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return map_[_Key];
  }

  bool contains(const _Kty& _Key) noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return map_.find(_Key) != map_.end();
  }

  bool find(const _Kty& _Key, _Ty& _Val) noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    auto it = map_.find(_Key);
    if (it != map_.end()) {
      _Val = it->second;
      return true;
    }
    return false;
  }

  template <class UnaryPredicate>
  void remove_if(UnaryPredicate&& p) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    for (auto it = map_.begin(); it != map_.end();) {
      if (p(*it)) {
        it = map_.erase(it);
      } else {
        ++it;
      }
    }
  }

  bool remove(const _Kty& _Key) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return map_.erase(_Key);
  }

  void erase(typename std::map<_Kty, _Ty, _Pr, _Alloc>::iterator __position) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return map_.erase(__position);
  }

  void for_each(
      const std::function<void(const _Kty&, const _Ty&)>& callback) noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    for (auto iter : map_) {
      callback(iter.first, iter.second);
    }
  }

  size_t size() const noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return map_.size();
  }

  void clear() noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    map_.clear();
  }

  std::recursive_mutex* get_mutex() noexcept { return &mutex_; }

 private:
  std::map<_Kty, _Ty, _Pr, _Alloc> map_;
  mutable std::recursive_mutex mutex_;
};

}  // namespace kviolet

#endif  //__KVIOLET__LOCK__MAP__