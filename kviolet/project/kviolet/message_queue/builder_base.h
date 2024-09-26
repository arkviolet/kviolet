#ifndef __KVIOLET__MESSAGE__QUEUE__BUILDER__BASE__H__
#define __KVIOLET__MESSAGE__QUEUE__BUILDER__BASE__H__

#include <algorithm>
#include <memory>

#include "../lock_container/lock_list.h"
#include "../poll/thread_poll.h"
#include "handler.h"

namespace kviolet {

class Message;

class MessageBuilderBase
    : public std::enable_shared_from_this<MessageBuilderBase> {
 public:
  explicit MessageBuilderBase() = default;
  explicit MessageBuilderBase(const std::string& name);

 public:
  std::shared_ptr<MessageBuilderBase> RegisterHandler(
      const std::shared_ptr<IHandler>& handler);

  std::shared_ptr<MessageBuilderBase> UnregisterHandler(
      const std::shared_ptr<IHandler>& handler);

  std::shared_ptr<MessageBuilderBase> UnregisterAllHandlers();

 public:
  virtual void Run(const std::shared_ptr<ThreadPool>& thread_pool,
                   const std::shared_ptr<Message>& message);

  virtual bool Send(const std::shared_ptr<Message>& message,
                    const uint64_t when) = 0;

  virtual bool Invoke(const std::shared_ptr<Message>& message,
                      const uint64_t when, const int64_t timeout_ms = -1) = 0;

 public:
  virtual std::shared_ptr<MessageBuilderBase> operator+=(
      const std::shared_ptr<IHandler>& handler) noexcept;

  virtual std::shared_ptr<MessageBuilderBase> operator-=(
      const std::shared_ptr<IHandler>& handler) noexcept;

 protected:
  virtual void OnHandler(const std::shared_ptr<ThreadPool>& thread_pool,
                         const std::shared_ptr<IHandler>& handler,
                         const std::shared_ptr<Message>& message);

 private:
  std::string name_;
  ConcurrentList<std::shared_ptr<IHandler>> handlers_;
};

}  // namespace kviolet

#endif  ///__KVIOLET__MESSAGE__QUEUE__BUILDER__BASE__H__
