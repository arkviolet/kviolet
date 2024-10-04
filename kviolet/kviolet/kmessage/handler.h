#ifndef __KVIOLET__MESSAGE__QUEUE__HANDLER__H__
#define __KVIOLET__MESSAGE__QUEUE__HANDLER__H__

#include <memory>
namespace kviolet {
namespace kmessage {

class Message;

class IHandler {
 public:
  virtual void RunInner(const std::shared_ptr<Message>& message) = 0;
};

class Handler : public IHandler {
 public:
  virtual void RunInner(const std::shared_ptr<Message>& message) override { Run(message); }

  virtual void Run(const std::shared_ptr<Message>& message) = 0;
};

}  // namespace kmessage
}  // namespace kviolet

#endif  ///__KVIOLET__MESSAGE__QUEUE__HANDLER__H__
