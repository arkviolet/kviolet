#include "singleton.h"

#include <iostream>

#include "../common/common.h"

namespace kviolet {
namespace module {

SingletonInterface* SingletonInterface::_ins = nullptr;

SingletonInterface::SingletonInterface() { _ins = this; }

SingletonInterface::~SingletonInterface() {}

void SingletonInterface::Handle(void* in, void* out) {
  (void)in;
  (void)out;

  KVIOLET_ASSERT_CPP_COND(0, "nothing");
}

}  // namespace module
}  // namespace kviolet