#ifndef __ACTOR__STATE__MACHINE__H__
#define __ACTOR__STATE__MACHINE__H__

#include <map>

#include "node.h"
#include "event.h"

namespace kviolet
{
    class StateMachine
    {
    public:
        StateMachine();

        ~StateMachine();

    public:
        /**
         * 初始根状态
         * */
        void Init(InterfaceFuncNode rootFuncNode);

        /**
         * 添加节点,与其他节点,root节点组成状态树
         * */
        void AddNode(InterfaceFuncNode funcNode);

        /**
         *  状态切换
         * */
        void JumpNode(InterfaceFuncNode funcNode);

    private:
        void EnterStatueNode(StatusNode *dst);

    public:
        virtual void Dispatch(std::shared_ptr<NodeEvent> e);

    private:
        StatusNode *_current{nullptr}; ///当前状态节点
        std::map<InterfaceFuncNode, StatusNode> _sateMap{};///状态表
    };
}
#endif //__ACTOR__STATE__MACHINE__H__