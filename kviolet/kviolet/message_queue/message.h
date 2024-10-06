#ifndef __KVIOLET__MESSAGE__QUEUE__MESSAGE__H__
#define __KVIOLET__MESSAGE__QUEUE__MESSAGE__H__

#include "builder.h"

namespace kviolet {
namespace message_queue {

class Message : public std::enable_shared_from_this<Message> {
 public:
  Message() = default;
  explicit Message(const Builder::Ptr &builder) : _builder(builder) {}
  virtual ~Message() {}

 public:
  void SetBuilder(const Builder::Ptr &builder) { _builder = builder; }

  void Run() { _builder->Run(shared_from_this()); }

  void Send();

 protected:
  Builder::Ptr _builder;
};

}  // namespace message_queue
}  // namespace kviolet

#endif  //__KVIOLET__MESSAGE__QUEUE__MESSAGE__H__