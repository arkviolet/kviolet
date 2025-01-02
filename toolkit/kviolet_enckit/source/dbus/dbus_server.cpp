#include "dbus_server.h"

namespace kviolet {
namespace enckit {

DBusServer::DBusServer(const std::string &name) : service_name_(name) {}

DBusServer::~DBusServer() {
  Destroy();
}

bool DBusServer::Initialize() {
  try {
    connection_ = std::move(sdbus::createSystemBusConnection(service_name_));
  } catch (const std::exception &e) {
    LOG(ERROR) << "OnInitialize failed:" << e.what();

    return false;
  }

  return true;
}

bool DBusServer::Start() {
  for (auto &iter : object_) {
    LOG(INFO) << "begin to register method on object: " << iter.first;
    try {
      iter.second->finishRegistration();
    } catch (const std::exception &e) {
      LOG(ERROR) << " registration failed:" << e.what();
      return false;
    }
  }

  return true;
}

void DBusServer::Stop() {
  connection_->leaveEventLoop();

  for (auto &iter : object_) {
    LOG(INFO) << "unregister method" << iter.first;
    iter.second->unregister();
  }
}

void DBusServer::Destroy() {
  connection_ = nullptr;
}

void DBusServer::Service() {
  connection_->enterEventLoop();
}

}  // namespace enckit
}  // namespace kviolet
