#ifndef __KVIOLET__ACTOR__STATE__MACHINE__H__
#define __KVIOLET__ACTOR__STATE__MACHINE__H__

#include <map>

#include "event.h"
#include "node.h"

namespace kviolet {
namespace actor {

class StateMachine {
 public:
  StateMachine();
  ~StateMachine();

 public:
  void Init(InterfaceFuncNode rootFuncNode);
  void AddNode(InterfaceFuncNode funcNode);
  void JumpNode(InterfaceFuncNode funcNode);

 private:
  void EnterStatueNode(StatusNode* dst);

 public:
  virtual void Dispatch(std::shared_ptr<NodeEvent> e);

 private:
  StatusNode* _current{nullptr};
  std::map<InterfaceFuncNode, StatusNode> _sateMap{};
};

}  // namespace actor
}  // namespace kviolet

#endif  //__KVIOLET__ACTOR__STATE__MACHINE__H__
