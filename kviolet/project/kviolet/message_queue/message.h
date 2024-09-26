#ifndef __KVIOLET__MESSAGE__QUEUE__MESSAGE__H__
#define __KVIOLET__MESSAGE__QUEUE__MESSAGE__H__

#include "../lock_container/lock_event.h"
#include "../poll/thread_poll.h"
#include "builder_base.h"

namespace kviolet {

class Message : public std::enable_shared_from_this<Message> {
 public:
  explicit Message() = default;
  explicit Message(const std::shared_ptr<MessageBuilderBase>& builder);
  virtual ~Message();

 public:
  void SetBuilder(const std::shared_ptr<MessageBuilderBase>& builder);

  uint64_t When();

  void SetWhen(const uint64_t when);

  void Join();

  bool Join(const int64_t timeout_ms);

  void Notify();

  void Run(const std::shared_ptr<ThreadPool>& pool);

  void Send(const uint64_t when = 0);

  void Invoke(const uint64_t when = 0);

 private:
  Message(Message&) = delete;
  Message& operator=(Message&) = delete;

 protected:
  uint64_t when_{0};
  LockEvent event_;
  std::shared_ptr<MessageBuilderBase> builder_;
};

}  // namespace kviolet

#endif  ///__KVIOLET__MESSAGE__QUEUE__MESSAGE__H__
