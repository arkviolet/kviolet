#ifndef __KVIOLET__ACTOR__ACTIVE__H__
#define __KVIOLET__ACTOR__ACTIVE__H__

#include <functional>
#include <future>
#include <memory>
#include <thread>

#include "hsm.h"
#include "queue.h"

namespace kviolet {
namespace actor {

class Handle;

class Active : public Hsm, public std::enable_shared_from_this<Active> {
 protected:
  explicit Active(PseudoState init, const std::shared_ptr<Handle>& handle);
  virtual ~Active();

 public:
  void Start();
  void Stop();

  void PushBack(const std::shared_ptr<Event>& event);
  void PushFront(const std::shared_ptr<Event>& event);

  /// event->_signal must >= 4 enum { EVENT_INIT, EVENT_ENTER, EVENT_EXIT, EVENT_EMPTY };
  void Subscribe(Signal event);

  /// event->_signal must >= 4 enum { EVENT_INIT, EVENT_ENTER, EVENT_EXIT, EVENT_EMPTY };
  void UnSubscribe(Signal event);

  /// event->_signal must >= 4 enum { EVENT_INIT, EVENT_ENTER, EVENT_EXIT, EVENT_EMPTY };
  void Publish(const std::shared_ptr<Event>& event);

 private:
  bool _running;
  std::shared_ptr<Handle> _handle;
  Deque<std::shared_ptr<Event>> _queue;
  std::shared_ptr<std::thread> _work_thread;
};

}  // namespace actor
}  // namespace kviolet

#endif  // __KVIOLET__ACTOR__ACTIVE__H__