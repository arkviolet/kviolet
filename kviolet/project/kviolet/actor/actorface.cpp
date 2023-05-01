#include "actorface.h"

namespace kviolet
{
    void Actor::Subscribe(Active *active, NodeSignal event)
    {
        std::lock_guard lock(_eventMutex);

        if (_subMap.end() == _subMap.find(event))
        {
            std::set<Active *> tmp;

            _subMap[event] = tmp;
        }

        _subMap[event].insert(active);
    }

    void Actor::UnSubscribe(Active *active, NodeSignal event)
    {
        std::lock_guard lock(_eventMutex);

        auto iter = _subMap.find(event);

        if (_subMap.end() != iter)
        {
            iter->second.erase(active);
        }
    }

    void Actor::Broadcast(std::shared_ptr<NodeEvent> event)
    {
        std::lock_guard lock(_eventMutex);

        auto iter = _subMap.find(event->_sig);

        if (iter != _subMap.end())
        {
            for (auto active:iter->second)
            {
                active->PushBack(event); /// 默认队列尾部添加
            }
        }
    }

    void Actor::RegisterActor(std::shared_ptr<Active> active)
    {
        /// active
        _activeList.push_back(active);
    }

    void Actor::Start()
    {
        for (auto &iter:_activeList)
        {
            iter->Start();
        }
    }

    void Actor::Stop()
    {
        for (auto &iter:_activeList)
        {
            iter->Stop();
        }
    }
}