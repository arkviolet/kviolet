#ifndef __KVIOLET__LOCK__EVENT__H__
#define __KVIOLET__LOCK__EVENT__H__

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace kviolet {
namespace container {

class LockEvent {
 public:
  void Notify(bool notify_all = false) noexcept;

  void Join();

  bool Join(uint64_t timeout);

 private:
  std::mutex _mutex;
  std::condition_variable _condition;
};

}  // namespace container
}  // namespace kviolet

#endif  // __KVIOLET__LOCK__EVENT__H__
