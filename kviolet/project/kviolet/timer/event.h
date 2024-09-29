#ifndef __KVIOLET__TIMER__EVENT__H__
#define __KVIOLET__TIMER__EVENT__H__

namespace kviolet {
namespace timer {
class ITimerEvent {
 public:
  ITimerEvent() = default;
  virtual ~ITimerEvent() = default;

 public:
  virtual void OnPause() = 0;
  virtual void OnResume() = 0;
  virtual void OnTrigger() = 0;
  virtual void OnStop(bool forced) = 0;
};

}  // namespace timer
}  // namespace kviolet

#endif  ///__KVIOLET__TIMER__EVENT__H__
