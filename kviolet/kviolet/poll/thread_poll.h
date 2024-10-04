#ifndef __KVIOLET__THREAD__POLL__H__
#define __KVIOLET__THREAD__POLL__H__

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace kviolet {
namespace kpoll {

class ThreadPool {
 public:
  explicit ThreadPool(std::size_t size = std::thread::hardware_concurrency());

  ~ThreadPool();

 public:
  template <typename FunctionTypeT, typename... Args>
  void Commit(FunctionTypeT&& function, Args&&... args) {
    auto task = std::bind(std::forward<FunctionTypeT>(function), std::forward<Args>(args)...);

    {
      std::lock_guard<std::mutex> lock(_mutex);

      _tasks.emplace([task]() { task(); });
    }

    _condition.notify_one();
  };

  void Release();

  void Wait();

  bool IsComplete();

  bool IsClose() const;

  std::size_t TaskSize() const;

  std::size_t ThreadSize() const;

 protected:
  void Create(std::size_t size);

 protected:
  std::mutex _mutex{};
  std::atomic<bool> _isClose{false};
  std::vector<std::thread> _pool{};
  std::atomic<std::size_t> _freeSize{0};
  std::condition_variable _condition{};
  std::queue<std::function<void()>> _tasks{};
};

}  // namespace kpoll
}  // namespace kviolet

#endif  ///__KVIOLET__THREAD__POLL__H__
