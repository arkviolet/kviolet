#include "statemachine.h"

namespace kviolet {
namespace actor {

StateMachine::StateMachine() {
  _current = new StatusNode();
}

StateMachine::~StateMachine() {
  delete _current;
  _current = nullptr;
}

void StateMachine::Init(InterfaceFuncNode rootFuncNode) {
  _current->_level = 0;
  _current->previousNode = nullptr;
  _current->_funNode = rootFuncNode;

  if (!_sateMap.empty()) {
    std::runtime_error("Init status map is not empty");
  }

  _sateMap.insert(std::make_pair(rootFuncNode, *_current));
}

void StateMachine::AddNode(InterfaceFuncNode funcNode) {
  if (_sateMap.end() != _sateMap.find(funcNode)) {
    std::runtime_error("Added repeatedly, affecting level");
  }

  StatusNode node;
  node._funNode = funcNode;

  {
    auto interface = (InterfaceFuncNode)funcNode(ActorDefault[EMPTY]);

    auto iter = _sateMap.find(interface);
    if (_sateMap.end() == iter) {
      std::runtime_error("Abnormal State,Error");
    }

    node.previousNode = &iter->second;
    node._level = iter->second._level + 1;
  }
}

void StateMachine::JumpNode(InterfaceFuncNode funcNode) {
  auto find = _sateMap.find(funcNode);

  if (_sateMap.end() == find) {
    std::runtime_error("Abnormal State,Error");
  }

  EnterStatueNode(&find->second);
}

void StateMachine::EnterStatueNode(StatusNode* dst) {
  std::vector<StatusNode*> enterVec, exitVec;

  auto sub = _current->_level - dst->_level;

  while (sub && sub--) {
    if (_current->_level > dst->_level) {
      exitVec.push_back(_current);

      _current = _current->previousNode;
    } else {
      enterVec.push_back(dst);

      dst = dst->previousNode;
    }
  }

  while (_current->previousNode != dst->previousNode) {
    exitVec.push_back(_current);
    enterVec.push_back(dst);
  }

  for (auto& iter : exitVec) {
    iter->_funNode(ActorDefault[EXIT]);
  }

  for (auto index = enterVec.size(); index; --index) {
    enterVec[index - 1]->_funNode(ActorDefault[ENTER]);
  }
}

void StateMachine::Dispatch(std::shared_ptr<NodeEvent> e) {
  auto state = _current->_funNode;
  do {
    state = (InterfaceFuncNode)state(e);
  } while (state != nullptr);
}

}  // namespace actor
}  // namespace kviolet