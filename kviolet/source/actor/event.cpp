#include "event.h"

namespace kviolet {
namespace actor {

Event::Event(Signal sig) : _signal(sig) {}

Event::~Event() {}

std::shared_ptr<Event> StdEventPtr[] = {
    std::make_shared<Event>(EVENT_INIT), std::make_shared<Event>(EVENT_ENTER),
    std::make_shared<Event>(EVENT_EXIT), std::make_shared<Event>(EVENT_EMPTY)};

}  // namespace actor
}  // namespace kviolet
