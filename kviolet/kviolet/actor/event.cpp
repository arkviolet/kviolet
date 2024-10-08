#include "event.h"

namespace kviolet {
namespace actor {

std::shared_ptr<NodeEvent> ActorDefault[] = {
    std::make_shared<NodeEvent>(INIT),
    std::make_shared<NodeEvent>(EXIT),
    std::make_shared<NodeEvent>(ENTER),
    std::make_shared<NodeEvent>(EMPTY),
};

}  // namespace actor
}  // namespace kviolet
