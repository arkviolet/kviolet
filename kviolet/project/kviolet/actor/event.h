#ifndef __ACTOR__EVENT__H__
#define __ACTOR__EVENT__H__

#include <memory>

namespace kviolet
{
    typedef unsigned int NodeSignal;

    typedef struct NodeEvent
    {
        explicit NodeEvent(NodeSignal sig) : _sig(sig)
        {}

        NodeSignal _sig;
    } NodeEvent;

    enum
    {
        INIT,
        EXIT,
        ENTER,
        EMPTY
    };

    extern std::shared_ptr<NodeEvent> ActorDefault[];
}
#endif //__ACTOR__EVENT__H__