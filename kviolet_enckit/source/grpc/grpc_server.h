#ifndef __KVIOLET__ENCKIT__GRPC__SERVER__H__
#define __KVIOLET__ENCKIT__GRPC__SERVER__H__

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>
#include <vector>

namespace kviolet {
namespace enckit {

class GRPCServer {
 public:
  explicit GRPCServer(const std::string &uri);
  GRPCServer() = delete;
  virtual ~GRPCServer();

 public:
  virtual void SetMaxReceiveMessageSize(int max_size);
  virtual bool RegisterService(const std::shared_ptr<::grpc::Service> &service);

 protected:
  virtual bool Initialize();
  virtual void Destroy();
  virtual bool Start();
  virtual void Stop();
  virtual void Service();

 protected:
  std::string uri_;
  ::grpc::ServerBuilder builder_;
  std::unique_ptr<::grpc::Server> server_;
  std::vector<std::shared_ptr<::grpc::Service>> services_;
};

}  // namespace enckit
}  // namespace kviolet

#endif  //__KVIOLET__ENCKIT__GRPC__SERVER__H__
