#ifndef __KVIOLET__LOCK__EVENT__
#define __KVIOLET__LOCK__EVENT__

#include <pthread.h>

#include <memory>
#include <mutex>
namespace kviolet {
namespace container {
class LockEvent {
 public:
  LockEvent() {
    pthread_condattr_init(&attr_);
    pthread_condattr_setclock(&attr_, CLOCK_MONOTONIC);
    pthread_cond_init(&cond_, &attr_);
  }

  ~LockEvent() {
    pthread_cond_destroy(&cond_);
    pthread_condattr_destroy(&attr_);
  }

 public:
  void Join() {
    std::unique_lock<std::mutex> lock(mutex_);
    pthread_cond_wait(&cond_, mutex_.native_handle());
  }

  bool Join(const int64_t timeout_ms) {
    if (timeout_ms < 0) {
      Join();
      return true;
    }

    struct timespec abs_time;
    clock_gettime(CLOCK_MONOTONIC, &abs_time);
    abs_time.tv_sec += timeout_ms / 1000;
    abs_time.tv_nsec += (timeout_ms % 1000) * 1e6;
    if (abs_time.tv_nsec >= 1e9) {
      abs_time.tv_sec++;
      abs_time.tv_nsec -= 1e9;
    }

    std::unique_lock<std::mutex> lock(mutex_);
    return pthread_cond_timedwait(&cond_, mutex_.native_handle(), &abs_time) == 0;
  }

  void Notify() { pthread_cond_broadcast(&cond_); }

 private:
  std::mutex mutex_;
  pthread_cond_t cond_;
  pthread_condattr_t attr_;
};

}  // namespace container
}  // namespace kviolet

#endif  //__KVIOLET__LOCK__EVENT__