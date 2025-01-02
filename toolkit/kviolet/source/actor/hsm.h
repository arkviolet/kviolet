#ifndef __KVIOLET__ACTOR__HSM__H__
#define __KVIOLET__ACTOR__HSM__H__

#include <memory>

#include "event.h"

namespace kviolet {
namespace actor {

class Hsm {  /// Hierarchical State Machine
 public:
  typedef void (Hsm::* PseudoState)(std::shared_ptr<Event>);
  typedef PseudoState (Hsm::* State)(std::shared_ptr<Event>);

 public:
  void Initialize();

  void Dispatch(const std::shared_ptr<Event>& event) {}

  bool IsIn(State state);

  bool IsSub(State child, State parent);

  State GetParentState(State child);

 protected:
  struct Tran {
    State myChain[16];
    unsigned int myActions;
  };

  Hsm(PseudoState initial);

  virtual ~Hsm();

  PseudoState Top(std::shared_ptr<Event>);

  void tran(State target);               // dynamic state transition
  void tranStat(Tran* t, State target);  // static state transition
  void init_(State target) { myState = target; }

 private:
  void tranSetup(Tran* t, State target);

 public:
  State myState;  // the active state
  State mySource;
};

typedef Hsm::PseudoState STATE;

}  // namespace actor
}  // namespace kviolet

#endif  // __KVIOLET__ACTOR__HSM__H__