#ifndef __ACTOR__NODE__H__
#define __ACTOR__NODE__H__

#include <functional>
#include <iostream>

#include "event.h"

/// typedef std::function<void(std::shared_ptr<NodeEvent> event)> FuncNode;
/// typedef std::function<FuncNode(std::shared_ptr<NodeEvent> event)> InterfaceFuncNode;

namespace kviolet {
namespace actor {

typedef void (*FuncNode)(std::shared_ptr<NodeEvent> event);

typedef FuncNode (*InterfaceFuncNode)(std::shared_ptr<NodeEvent> event);

typedef struct StatusNode {
  uint32_t _level{0};
  InterfaceFuncNode _funNode{nullptr};
  StatusNode* previousNode{nullptr};
} StatusNode;

}  // namespace actor
}  // namespace kviolet

#endif  ///__ACTOR__NODE__H__