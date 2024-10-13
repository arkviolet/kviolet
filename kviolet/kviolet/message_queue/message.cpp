
#include "message.h"

#include "../utilities/timestamp.h"

namespace kviolet {
namespace message_queue {

void Message::Send(uint64_t when) {
  _when = when ? when + utilities::Timestamp::MonotonicMilliseconds() : 0;
  _builder->Send(shared_from_this());
}

uint64_t Message::When() { return _when; }

}  // namespace message_queue
}  // namespace kviolet
