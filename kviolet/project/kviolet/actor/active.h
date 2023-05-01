#ifndef __ACTOR__ACTIVE__H__
#define __ACTOR__ACTIVE__H__

#include <atomic>
#include <thread>


#include "node.h"
#include "event.h"
#include "lockqueue.h"
#include "statemachine.h"

namespace kviolet
{
    class Actor;

    class Active : public StateMachine
    {
    public:
        Active(std::shared_ptr<Actor> actor) : _actor(actor)
        {

        }

        ~Active() = default;

    public:

        virtual void Stop();

        virtual void Start();

        virtual void PushBack(std::shared_ptr<NodeEvent> e);

        virtual void PushFront(std::shared_ptr<NodeEvent> e);

        virtual void Subscribe(NodeSignal event);

        virtual void Unsubscribe(NodeSignal event);

        virtual void Broadcast(std::shared_ptr<NodeEvent> e);

    private:
        std::thread _runThread;
        std::atomic<bool> _running;
        std::shared_ptr<Actor> _actor;
        LockCQueue<std::shared_ptr<NodeEvent>> _lockQueue;
    };
}

#endif //__ACTOR__ACTIVE__H__