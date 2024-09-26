#ifndef __KVIOLET__MESSAGE__MESSAGE__BUILDER__H__
#define __KVIOLET__MESSAGE__MESSAGE__BUILDER__H__

#include "../poll/thread_poll.h"
#include "builder_base.h"
#include "looper.h"
#include "message.h"

namespace kviolet {

class MessageBuilder : public MessageBuilderBase {
 public:
  class FunctionHandler : public IHandler {
   public:
    using Callback = std::function<void(const std::shared_ptr<Message>&)>;

   public:
    explicit FunctionHandler(const Callback& callback) : callback_(callback) {}

   public:
    virtual void RunInner(const std::shared_ptr<Message>& message) override {
      callback_(message);
    }

   protected:
    Callback callback_;
  };

 public:
  explicit MessageBuilder();
  explicit MessageBuilder(const std::string& name);
  explicit MessageBuilder(const std::shared_ptr<Looper>& looper);
  explicit MessageBuilder(const std::string& name,
                          const std::shared_ptr<Looper>& looper);

 public:
  virtual std::shared_ptr<MessageBuilderBase> RegisterHandler(
      const typename FunctionHandler::Callback& callback);

  virtual std::shared_ptr<Message> Build();

  virtual bool Send(const std::shared_ptr<Message>& message,
                    const uint64_t when);

  virtual bool Invoke(const std::shared_ptr<Message>& message,
                      const uint64_t when, const int64_t timeout_ms = -1);

 public:
  virtual std::shared_ptr<MessageBuilderBase> operator+=(
      const std::shared_ptr<IHandler>& handler) noexcept override {
    return MessageBuilderBase::RegisterHandler(handler);
  }

  virtual std::shared_ptr<MessageBuilderBase> operator+=(
      const typename FunctionHandler::Callback& callback) noexcept {
    return RegisterHandler(callback);
  }

 private:
  MessageBuilder(MessageBuilder&) = delete;
  MessageBuilder& operator=(MessageBuilder&) = delete;

 private:
  std::shared_ptr<Looper> looper_;
};

class AsyncMessageBuilder : public MessageBuilder {
 public:
  virtual bool Invoke(const std::shared_ptr<Message>& message,
                      const uint64_t when, const int64_t timeout_ms = -1);

 protected:
  virtual void OnHandler(const std::shared_ptr<ThreadPool>& pool,
                         const std::shared_ptr<IHandler>& handler,
                         const std::shared_ptr<Message>& message);
};

}  // namespace kviolet

#endif  ///__KVIOLET__MESSAGE__MESSAGE__BUILDER__H__
