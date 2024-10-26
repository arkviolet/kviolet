#include "grpc_server.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>

namespace kviolet {
namespace enckit {

GRPCServer::GRPCServer(const std::string &uri) : uri_(uri) {}

GRPCServer::~GRPCServer() {}

void GRPCServer::SetMaxReceiveMessageSize(int max_size) {
  builder_.SetMaxReceiveMessageSize(max_size);
}

bool GRPCServer::RegisterService(const std::shared_ptr<::grpc::Service> &service) {
  builder_.RegisterService(service.get());
  services_.push_back(service);

  return true;
}

bool GRPCServer::Initialize() {
  ::grpc::EnableDefaultHealthCheckService(true);
  ::grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  builder_.AddListeningPort(uri_, ::grpc::InsecureServerCredentials());

  return true;
}

void GRPCServer::Destroy() {
  services_.clear();
}

bool GRPCServer::Start() {
  server_ = builder_.BuildAndStart();

  return server_ != nullptr;
}

void GRPCServer::Stop() {
  if (server_) {
    server_->Shutdown();
  }
  server_ = nullptr;
}

void GRPCServer::Service() {
  server_->Wait();
}

}  // namespace enckit
}  // namespace kviolet
