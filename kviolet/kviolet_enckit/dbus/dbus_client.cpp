
#include "dbus_client.h"

namespace kviolet {
namespace enckit {

DBusClient::DBusClient(const std::shared_ptr<sdbus::IConnection> &connection) : connection_(connection) {}

DBusClient::DBusClient(const std::string &connection_name)
    : connection_name_(connection_name), connection_(sdbus::createSystemBusConnection().release()) {
  if (connection_name_ != "") {
    connection_->requestName(connection_name_);
  }
}

DBusClient::~DBusClient() {
  for (auto &it : proxy_) {
    it.second->unregister();
  }

  if (connection_.use_count() == 1 && start_event_loop_) {
    connection_->leaveEventLoop();
  }
  if (connection_name_ != "") {
    connection_->releaseName(connection_name_);
  }
}

bool DBusClient::SubscribeSignal(const std::string &service_name,
                                 const std::string &object_path,
                                 const std::string &interface_name,
                                 const std::string &signal_name,
                                 const sdbus::signal_handler &handler) {
  std::call_once(event_loop_once_, [this]() {
    LOG(INFO) << "begin dbus event loop";
    connection_->enterEventLoopAsync();
    start_event_loop_ = true;
  });

  auto proxy = sdbus::createProxy(*connection_, service_name, object_path);
  try {
    proxy->registerSignalHandler(interface_name, signal_name, handler);
  } catch (const sdbus::Error &e) {
    LOG(ERROR) << "dbus error: name = " << e.getName() << " message = " << e.getMessage();
    return false;
  }
  proxy->finishRegistration();

  std::string signal_id = service_name + object_path + interface_name + signal_name;
  proxy_.emplace(std::move(signal_id), std::move(proxy));

  return true;
}

bool DBusClient::UnSubscribeSignal(const std::string &service_name,
                                   const std::string &object_path,
                                   const std::string &interface_name,
                                   const std::string &signal_name) {
  std::string signal_id = service_name + object_path + interface_name + signal_name;
  auto it = proxy_.find(signal_id);
  if (it != proxy_.end()) {
    LOG(INFO) << "found, begin to unregister signal!";
    it->second->unregisterSignalHandler(interface_name, signal_name);
    proxy_.erase(it);
    return true;
  } else {
    LOG(WARNING) << "not found, may be never subscribe this signal before!";
    return false;
  }
}

}  // namespace enckit
}  // namespace kviolet
