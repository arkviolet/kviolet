#ifndef __KVIOLET__LOCK__MAP__
#define __KVIOLET__LOCK__MAP__

#include <functional>
#include <map>
#include <mutex>

namespace kviolet {
namespace container {

template <class TypeK, class TypeV, class _Pr = std::less<TypeK>, class _Alloc = std::allocator<std::pair<const TypeK, TypeV>>>
class LockMap {
 public:
  using key_type = TypeK;
  using mapped_type = TypeV;
  using value_type = std::pair<const TypeK, TypeV>;

 public:
  template <class _Valty>
  void Insert(_Valty&& value) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    value_.insert(std::forward<_Valty>(value));
  }

  TypeV& operator[](const TypeK& key) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return value_[key];
  }

  bool IsExist(const TypeK& key) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return value_.find(key) != value_.end();
  }

  bool Find(const TypeK& key, TypeV& value) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    auto it = value_.find(key);
    if (it != value_.end()) {
      value = it->second;
      return true;
    }
    return false;
  }

  template <class UnaryPredicate>
  void RemoveIf(UnaryPredicate&& p) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    for (auto it = value_.begin(); it != value_.end();) {
      if (p(*it)) {
        it = value_.erase(it);
      } else {
        ++it;
      }
    }
  }

  bool Remove(const TypeK& key) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return value_.erase(key);
  }

  void Erase(typename std::map<TypeK, TypeV, _Pr, _Alloc>::iterator pos) {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return value_.erase(pos);
  }

  void ForEach(const std::function<void(const TypeK&, const TypeV&)>& callback) noexcept {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    for (auto iter : value_) {
      callback(iter.first, iter.second);
    }
  }

  size_t Size() const {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    return value_.size();
  }

  void Clear() {
    std::lock_guard<std::recursive_mutex> lk(mutex_);
    value_.clear();
  }

  std::recursive_mutex* GetMutex() { return &mutex_; }

 private:
  mutable std::recursive_mutex mutex_;
  std::map<TypeK, TypeV, _Pr, _Alloc> value_;
};

}  // namespace container
}  // namespace kviolet

#endif  //__KVIOLET__LOCK__MAP__