#ifndef __KVIOLET__TIMER__NODE__H__
#define __KVIOLET__TIMER__NODE__H__

#include <ctime>
#include <iostream>
#include <memory>

#include "event.h"

namespace kviolet {
namespace timer {

class TimerNode {
 public:
  TimerNode(const std::shared_ptr<ITimerEvent>& event, int64_t count, std::time_t expire, std::time_t interval);
  ~TimerNode();

 public:
  void Trigger();
  void Pause(std::time_t tick);
  void Resume(std::time_t tick);
  void RevisedExpire(std::time_t tick);
  void Destroy();

  std::time_t Expire();
  std::shared_ptr<ITimerEvent> Event();

  bool IsValid();
  bool IsPause();

 protected:
  bool _isValid{true};
  bool _isPause{false};

  uint64_t _count{0};
  std::time_t _expire{0};
  std::time_t _interval{0};
  std::time_t _pauseTick{0};
  std::shared_ptr<ITimerEvent> _event{nullptr};
};

}  // namespace timer
}  // namespace kviolet

#endif  ///__KVIOLET__TIMER__NODE__H__
