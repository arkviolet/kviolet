#ifndef __ACTOR__ACTOR__FACE__H__
#define __ACTOR__ACTOR__FACE__H__

#include <map>
#include <set>
#include <vector>
#include "active.h"

namespace kviolet {
namespace actor {
class Actor {
 public:
  Actor() = default;
  ~Actor() = default;

 public:
  void Subscribe(Active* active, NodeSignal event);
  void UnSubscribe(Active* active, NodeSignal event);
  void Broadcast(std::shared_ptr<NodeEvent> event);
  void RegisterActor(std::shared_ptr<Active> active);
  void Start();
  void Stop();

 private:
  std::mutex _eventMutex;
  std::map<NodeSignal, std::set<Active*>> _subMap;
  std::vector<std::shared_ptr<Active>> _activeList;
};

}  // namespace actor
}  // namespace kviolet

#endif  //__ACTOR__ACTOR__FACE__H__
