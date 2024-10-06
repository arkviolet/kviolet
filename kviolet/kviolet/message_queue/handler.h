#ifndef __KVIOLET__MESSAGE__QUEUE__HANDLER__H__
#define __KVIOLET__MESSAGE__QUEUE__HANDLER__H__

#include <functional>
#include <memory>
namespace kviolet {
namespace message_queue {

class Message;

class Handler {
 public:
  using Prt = std::shared_ptr<Handler>;
  using Callback = std::function<void(const std::shared_ptr<Message>&)>;

 public:
  Handler() = delete;
  explicit Handler(Callback cb) : _cb(cb) {}
  virtual ~Handler() = default;

 public:
  void Run(const std::shared_ptr<Message>& message) { _cb(message); }

 private:
  Callback _cb;
};

}  // namespace message_queue
}  // namespace kviolet

#endif  //__KVIOLET__MESSAGE__QUEUE__HANDLER__H__
