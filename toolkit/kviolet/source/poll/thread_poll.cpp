#include "thread_poll.h"

#include "../common/common.h"

namespace kviolet {
namespace kpoll {

ThreadPool::ThreadPool(std::size_t size) {
  _isClose.store(false);
  _freeSize.store(size);
  Create(size);
}

ThreadPool::~ThreadPool() {
  Release();
}

void ThreadPool::Release() {
  if (_isClose.load()) {
    return;
  }

  _isClose.store(true);
  _condition.notify_all();

  for (auto& thread : _pool) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void ThreadPool::Wait() {
  while (!IsComplete()) {
    KVIOLET_THIS_THREAD_SLEEP_MS(10);
  }
}

bool ThreadPool::IsComplete() {
  return _tasks.empty() && _freeSize.load() == _pool.size();
}

bool ThreadPool::IsClose() const {
  return _isClose.load();
}

std::size_t ThreadPool::TaskSize() const {
  return _tasks.size();
}

std::size_t ThreadPool::ThreadSize() const {
  return _pool.size();
}

void ThreadPool::Create(std::size_t size) {
  for (std::size_t i = 0; i < size; ++i) {
    _pool.emplace_back([this] {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(_mutex);
          _condition.wait(lock, [this] { return !_tasks.empty() || _isClose.load(); });

          if (_isClose.load()) {
            return false;
          }

          task = std::move(_tasks.front());
          _tasks.pop();
        }

        --_freeSize;

        task();

        ++_freeSize;
      }
    });
  }
}

}  // namespace kpoll
}  // namespace kviolet
