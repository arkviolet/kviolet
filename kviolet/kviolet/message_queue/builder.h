#ifndef __KVIOLET__MESSAGE__QUEUE__BUILDER__H__
#define __KVIOLET__MESSAGE__QUEUE__BUILDER__H__

#include <string>

#include "../lock_container/lock_list.h"
#include "handler.h"

namespace kviolet {
namespace message_queue {

using namespace kviolet::container;

class Message;

class Builder : public std::enable_shared_from_this<Builder> {
 public:
  using Ptr = std::shared_ptr<Builder>;

 public:
  explicit Builder(const std::string &name = "kviolet") : _name(name) {}
  virtual ~Builder() {}

 public:
  Ptr RegisterHandler(const std::shared_ptr<Handler> &handler) {
    _handler_list.PushBack(handler);
    return shared_from_this();
  }

  template <typename _Ty, typename... _Args>
  Ptr RegisterHandlers(const _Ty &value, _Args &...args) {
    RegisterHandler(value);

    if constexpr (sizeof...(args) > 0) {  /// C++17
      return RegisterHandlers(args...);
    }

    return shared_from_this();
  }

  Ptr UnRegisterHandler() {
    _handler_list.Clear();
    return shared_from_this();
  }

  Ptr UnRegisterHandler(const std::shared_ptr<Handler> &handler) {
    _handler_list.Remove(handler);
    return shared_from_this();
  }

  template <typename _Tp, typename... _Args>
  Ptr UnRegisterHandlers(const _Tp &value, _Args... args) {
    UnRegisterHandler(value);
    if constexpr (sizeof...(args) > 0) {  /// C++17
      return UnRegisterHandlers(value);
    }

    return shared_from_this();
  }

  Ptr operator+=(const std::shared_ptr<Handler> &handler) { return RegisterHandler(handler); }
  Ptr operator-=(const std::shared_ptr<Handler> &handler) { return UnRegisterHandler(handler); }

 public:
  void Run(const std::shared_ptr<Message> &message) {
    _handler_list.ForEach(
        [&](const std::shared_ptr<Handler> &handler) { OnHandler(handler, message); });
  }

  std::shared_ptr<Message> Build();

  bool Send(const std::shared_ptr<Message> &message);

 protected:
  void OnHandler(const std::shared_ptr<Handler> &handler, const std::shared_ptr<Message> &message) {
    handler->Run(message);
  }

 private:
  std::string _name;
  LockList<std::shared_ptr<Handler>> _handler_list;
};

}  // namespace message_queue
}  // namespace kviolet

#endif  //__KVIOLET__MESSAGE__QUEUE__BUILDER__H__