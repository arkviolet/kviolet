#ifndef __KVIOLET__MODULE__SINGLETON__H__
#define __KVIOLET__MODULE__SINGLETON__H__

namespace kviolet {
namespace module {

class SingletonInterface {
 public:
  static SingletonInterface* Instance() { return _ins; }
  virtual void Handle(void* in, void* out);

 protected:
  SingletonInterface();
  virtual ~SingletonInterface();

  SingletonInterface(const SingletonInterface&) = delete;
  SingletonInterface& operator=(const SingletonInterface&) = delete;

  static SingletonInterface* _ins;
};

template <class _Tp>
class Singleton {
 public:
  static _Tp& Instance() {
    /// TODO std::mutex
    static _Tp ins;
    return ins;
  }

 public:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

 protected:
  Singleton() = default;
};

}  // namespace module
}  // namespace kviolet

#endif  // __KVIOLET__MODULE__SINGLETON__H__
