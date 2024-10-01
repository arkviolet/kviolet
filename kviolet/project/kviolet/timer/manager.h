#ifndef __KVIOLET__TIMER__MANAGER__H__
#define __KVIOLET__TIMER__MANAGER__H__

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "node.h"

namespace kviolet {
namespace timer {

#define TIMER_WHEEL_NUM 4
#define TIMER_NEAR_BITS 8
#define TIMER_WHEEL_BITS 6

/**
 *      level-1   0 1 2 3 .......... 254 255   2^8  (TIMER_NEAR_BITS)
 *      level-2   0 1 2 3 .......... 62  63    2^6  (TIMER_WHEEL_BITS)
 *      level-3   0 1 2 3 .......... 62  63    2^6  (TIMER_WHEEL_BITS)
 *      level-4   0 1 2 3 .......... 62  63    2^6  (TIMER_WHEEL_BITS)
 *      level-5   0 1 2 3 .......... 62  63    2^6  (TIMER_WHEEL_BITS)
 */

class TimerManager {
 public:
  TimerManager();
  ~TimerManager();

 public:
  bool Start(const std::shared_ptr<ITimerEvent>& event, int64_t count, std::time_t interval);
  bool Start(std::function<void()> function, int64_t count, std::time_t interval);
  void Stop();
  void Destroy(const std::shared_ptr<ITimerEvent>& enevt);
  bool Pause(const std::shared_ptr<ITimerEvent>& enevt);
  bool Resume(const std::shared_ptr<ITimerEvent>& enevt);

 protected:
  void DriverThread();
  void Update();
  void Executes();
  void AddNode(std::shared_ptr<TimerNode>& node);
  bool Cascade(std::size_t wheel, std::size_t index);
  void ClearSpokes(std::vector<std::shared_ptr<TimerNode>>& spokesList);

 protected:
  bool _running{true};
  std::mutex _lock{};
  std::thread _thread{};
  std::atomic<std::time_t> _tickTime{0};
  std::atomic<std::time_t> _lastTime{0};
  std::vector<std::shared_ptr<TimerNode>> _nearList[(1 << TIMER_NEAR_BITS)]{};
  std::vector<std::shared_ptr<TimerNode>> _wheelList[TIMER_WHEEL_NUM][(1 << TIMER_WHEEL_BITS)]{};

  std::map<std::shared_ptr<ITimerEvent>, std::shared_ptr<TimerNode>> _pause{};
  std::map<std::shared_ptr<ITimerEvent>, std::shared_ptr<TimerNode>> _normal{};
  std::map<std::shared_ptr<ITimerEvent>, std::shared_ptr<TimerNode>> _manager{};
};

}  // namespace timer
}  // namespace kviolet

#endif  // __KVIOLET__TIMER__MANAGER__H__
