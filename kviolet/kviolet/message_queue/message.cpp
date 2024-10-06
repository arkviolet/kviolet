
#include "message.h"

namespace kviolet {
namespace message_queue {

void Message::Send() { _builder->Send(shared_from_this()); }

}  // namespace message_queue
}  // namespace kviolet
