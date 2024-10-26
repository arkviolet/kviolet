#ifndef __KVIOLET__ENCKIT__GRPC__SERVER__LOOP__H__
#define __KVIOLET__ENCKIT__GRPC__SERVER__LOOP__H__

#include <grpcpp/grpcpp.h>
#include <kviolet/lock_container/lock_list.h>
#include <kviolet/lock_container/lock_map.h>

#include <memory>
#include <thread>
#include <utility>

namespace kviolet {
namespace enckit {

using namespace kviolet::container;

template <class DataType>
class GrpcServiceLoop {
  struct Context {
    LockList<std::shared_ptr<DataType>> list_;
  };

 public:
  void send(const std::shared_ptr<DataType> &data) {
    map_.ForEach([&](auto sctx, auto ctx) { ctx->list_.push_back(data); });
  }

  bool loop(::grpc::ServerContext *context,
            const std::function<bool(const std::shared_ptr<DataType> &data)> &callback,
            const int read_timeout = 1000) {
    auto ctx = std::make_shared<Context>();
    if (ctx == nullptr) {
      return false;
    }

    map_.Insert(std::pair<::grpc::ServerContext *, std::shared_ptr<Context>>({context, ctx}));

    LOG(INFO) << "start loop: " << std::this_thread::get_id() << ", " << context->peer();

    std::shared_ptr<DataType> data;
    while (!context->IsCancelled()) {
      if (ctx->list_.try_pop_front(read_timeout, data)) {
        if (!callback(data)) {
          LOG(INFO) << "close by writter: " << std::this_thread::get_id() << ", "
                    << context->peer();
          break;
        }
      }
    }

    map_.remove(context);
    LOG(INFO) << "end loop: " << std::this_thread::get_id();

    return true;
  }

 private:
  LockMap<::grpc::ServerContext *, std::shared_ptr<Context>> map_;
};

}  // namespace enckit
}  // namespace kviolet

#endif  //__KVIOLET__ENCKIT__GRPC__SERVER__LOOP__H__
