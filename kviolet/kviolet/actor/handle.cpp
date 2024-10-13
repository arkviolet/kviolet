#include "handle.h"

namespace kviolet {
namespace actor {

void Handle::Subscribe(const std::shared_ptr<Active>& active, Signal event) {
  std::lock_guard<std::mutex> lock(_mutex);

  auto find = _subscribe_map.find(event);
  if (find == _subscribe_map.end()) {
    _subscribe_map[event] = std::set<std::shared_ptr<Active>>();
  }

  _subscribe_map[event].insert(active);
}

void Handle::UnSubscribe(const std::shared_ptr<Active>& active, Signal event) {
  std::lock_guard<std::mutex> lock(_mutex);
  auto find = _subscribe_map.find(event);
  if (find == _subscribe_map.end()) {
    return;
  }

  find->second.erase(active);
}

void Handle::Publish(const std::shared_ptr<Event>& event) {
  std::lock_guard<std::mutex> lock(_mutex);
  auto iter = _subscribe_map.find(event->_signal);
  if (iter == _subscribe_map.end()) {
    return;
  }

  for (auto active : iter->second) {
    active->PushBack(event);
  }
}

void Handle::RegisterActor(const std::shared_ptr<Active>& actor) {
  actor->Initialize();
  _actors.push_back(actor);
}

void Handle::start() {
  for (auto& actor : _actors) {
    actor->Start();
  }
}

}  // namespace actor
}  // namespace kviolet
