#include "active.h"
#include "actorface.h"

namespace kviolet
{
    void Active::Start()
    {
        _running = true;

        auto func = [this]()
        {
            std::shared_ptr<NodeEvent> node;

            while (_running)
            {
                _lockQueue.WaiAndPop(node); /// wait data

                Dispatch(node);
            }

        };

        _runThread = std::move(std::thread(func));
    }

    void Active::PushBack(std::shared_ptr<NodeEvent> e)
    {
        _lockQueue.Push(e);
    }

    void Active::PushFront(std::shared_ptr<NodeEvent> e)
    {
        _lockQueue.Push(e); /// TODO Push Front
    }

    void Active::Subscribe(NodeSignal event)
    {
        _actor->Subscribe(this, event);
    }

    void Active::Unsubscribe(NodeSignal event)
    {
        _actor->UnSubscribe(this, event);
    }

    void Active::Broadcast(std::shared_ptr<NodeEvent> event)
    {
        _actor->Broadcast(event);
    }
}