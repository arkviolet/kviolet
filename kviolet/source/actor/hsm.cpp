#ifndef __KVIOLET__ACTOR__QUEUE__H__
#define __KVIOLET__ACTOR__QUEUE__H__

#include "hsm.h"

#include "event.h"

#define TRIGGER(state_, sig_) (State)((this->*(state_))(StdEventPtr[sig_]))

namespace kviolet {
namespace actor {

Hsm::Hsm(PseudoState initial) : myState(&Hsm::Top), mySource((State)initial) {}

Hsm::~Hsm() {}

STATE Hsm::Top(std::shared_ptr<Event>) { return 0; }

void Hsm::Initialize() {}

}  // namespace actor
}  // namespace kviolet

#endif  // __KVIOLET__ACTOR__QUEUE__H__