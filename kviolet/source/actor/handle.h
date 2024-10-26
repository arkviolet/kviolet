#ifndef __KVIOLET__ACTOR__HANDLE__H__
#define __KVIOLET__ACTOR__HANDLE__H__

#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <vector>

#include "active.h"

namespace kviolet {
namespace actor {

class Handle {
 public:
  Handle() = default;
  ~Handle() = default;

 public:
  void Subscribe(const std::shared_ptr<Active>& active, Signal event);

  void UnSubscribe(const std::shared_ptr<Active>& active, Signal event);

  void Publish(const std::shared_ptr<Event>& event);

  void RegisterActor(const std::shared_ptr<Active>& actor);

  void start();

 private:
  std::mutex _mutex;
  std::vector<std::shared_ptr<Active>> _actors;
  std::map<Signal, std::set<std::shared_ptr<Active>>> _subscribe_map;
};

}  // namespace actor
}  // namespace kviolet

#endif  // __KVIOLET__ACTOR__HANDLE__H__