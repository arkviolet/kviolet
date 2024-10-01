
#include "node.h"

namespace kviolet {
namespace timer {

TimerNode::TimerNode(const std::shared_ptr<ITimerEvent>& event, int64_t count, std::time_t expire, std::time_t interval)
    : _count(count), _expire(expire), _interval(interval), _event(event) {}

TimerNode::~TimerNode() {
  Destroy();
}

void TimerNode::Destroy() {
  if (_isValid) {
    _isValid = false;
    _event->OnStop(true);
  }
}

void TimerNode::Trigger() {
  if (_isValid) {
    _expire += _interval;

    if (_count) {
      _event->OnTrigger();
      --_count;
    }
  }

  if (0 == _count) {
    _isValid = false;
    _event->OnStop(false);
  }
}

void TimerNode::Pause(std::time_t tick) {
  if (_isValid && !_isPause) {
    _isPause = true;

    _pauseTick = tick;

    _event->OnPause();
  }
}

void TimerNode::Resume(std::time_t tick) {
  if (_isValid && _isPause) {
    _expire = tick + _expire - _pauseTick;

    _isPause = false;

    _event->OnResume();
  }
}

void TimerNode::RevisedExpire(std::time_t tick) {
  auto interval = _expire - tick;

  if (interval < 0 && std::abs(interval) > _interval) {
    _expire += (std::abs(interval) / _interval) * _interval;
  }
}

bool TimerNode::IsValid() {
  return _isValid;
}

bool TimerNode::IsPause() {
  return _isPause;
}

std::time_t TimerNode::Expire() {
  return _expire;
}

std::shared_ptr<ITimerEvent> TimerNode::Event() {
  return _event;
}

}  // namespace timer
}  // namespace kviolet
