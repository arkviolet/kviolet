#ifndef __KVIOLET__LOCK__MAP__H__
#define __KVIOLET__LOCK__MAP__H__

#include <functional>
#include <map>
#include <mutex>

namespace kviolet {
namespace container {

template <class _Tpkey, class _TpValue>
class LockMap {
 public:
  template <class _Valty>
  void Insert(_Valty&& value) {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    _value.insert(std::forward<_Valty>(value));
  }

  _TpValue& operator[](const _Tpkey& key) {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    return _value[key];
  }

  bool IsExist(const _Tpkey& key) {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    return _value.end() != _value.find(key);
  }

  bool Find(const _Tpkey& key, _TpValue& value) {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    auto find = _value.find(key);
    if (find != _value.end()) {
      value = find->second;
      return true;
    }
    return false;
  }

  template <typename _Pre>
  void RemoveIf(_Pre p) {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    for (auto it = _value.begin(); it != _value.end();) {
      if (p(*it)) {
        it = _value.erase(it);
      } else {
        ++it;
      }
    }
  }

  bool Remove(const _Tpkey& key) {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    return _value.erase(key);
  }

  void ForEach(const std::function<void(const _Tpkey&, const _TpValue&)>& cb) noexcept {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    for (auto& iter : _value) {
      cb(iter.first, iter.second);
    }
  }

  size_t Size() const {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    return _value.size();
  }

  void Clear() {
    std::lock_guard<std::recursive_mutex> lk(_mutex);
    _value.clear();
  }

  std::recursive_mutex* GetMutex() { return &_mutex; }

 private:
  std::map<_Tpkey, _TpValue> _value;
  mutable std::recursive_mutex _mutex;
};

}  // namespace container
}  // namespace kviolet

#endif  //__KVIOLET__LOCK__MAP__H__