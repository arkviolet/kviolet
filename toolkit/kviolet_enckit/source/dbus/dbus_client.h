#ifndef __KVIOLET__ENCKIT__DBUS__CLIENT__H__
#define __KVIOLET__ENCKIT__DBUS__CLIENT__H__

#include <glog/logging.h>
#include <sdbus-c++/sdbus-c++.h>

#include <memory>
#include <mutex>
#include <string>
namespace kviolet {
namespace enckit {

class DBusClient {
 public:
  explicit DBusClient(const std::shared_ptr<sdbus::IConnection> &connection);
  explicit DBusClient(const std::string &connection_name = "");
  ~DBusClient();

 public:
  template<typename... _Args>
  bool CallMethod(const std::string &service_name,
                  const std::string &object_path,
                  const std::string &interface_name,
                  const std::string &method_name,
                  _Args &&... args) {
    try {
      auto proxy = sdbus::createProxy(*connection_, service_name, object_path);
      proxy->callMethod(method_name).onInterface(interface_name).withArguments(std::forward<_Args>(args)...);
    } catch (const sdbus::Error &e) {
      LOG(ERROR) << "name:" << e.getName() << "message:" << e.getMessage();
      return false;
    }

    return true;
  }

  template<typename T, typename... Args>
  T CallMethod(const std::string &service_name,
               const std::string &object_path,
               const std::string &interface_name,
               const std::string &method_name,
               Args &&... args) {
    T result;
    try {
      auto proxy = sdbus::createProxy(*connection_, service_name, object_path);
      proxy->callMethod(method_name).onInterface(interface_name).withArguments(std::forward<Args>(args)...).storeResultsTo(
          result);
    } catch (const sdbus::Error &e) {
      LOG(ERROR) << "name:" << e.getName() << "message:" << e.getMessage();
    }

    return result;
  }

  template<typename... _Args>
  bool EmitSignal(const std::string &object_path,
                  const std::string &interface_name,
                  const std::string &signal_name,
                  _Args &&... args) {
    auto object = sdbus::createObject(*connection_, object_path);
    auto signal = object->createSignal(interface_name, signal_name);
    (void) (signal << ... << args);

    try {
      signal.send();
    } catch (const sdbus::Error &e) {
      LOG(ERROR) << "name:" << e.getName() << "message:" << e.getMessage();
      return false;
    }

    return true;
  }

  bool SubscribeSignal(const std::string &service_name,
                       const std::string &object_path,
                       const std::string &interface_name,
                       const std::string &signal_name,
                       const sdbus::signal_handler &handler);

  bool UnSubscribeSignal(const std::string &service_name,
                         const std::string &object_path,
                         const std::string &interface_name,
                         const std::string &signal_name);

 private:
  std::string connection_name_;
  std::shared_ptr<sdbus::IConnection> connection_;
  std::map<std::string, std::unique_ptr<sdbus::IProxy>> proxy_;
  std::once_flag event_loop_once_;
  bool start_event_loop_{false};
};

template<typename... Args>
bool CallMethod(const std::string &service_name,
                const std::string &object_path,
                const std::string &interface_name,
                const std::string &methd_name,
                Args &&... args) {
  DBusClient client;
  return client.CallMethod(service_name, object_path, interface_name, methd_name, std::forward<Args>(args)...);
}

template<typename T, typename... Args>
T CallMethod(const std::string &service_name,
             const std::string &object_path,
             const std::string &interface_name,
             const std::string &methd_name,
             Args &&... args) {
  DBusClient client;
  return client.CallMethod<T, Args...>(service_name,
                                       object_path,
                                       interface_name,
                                       methd_name,
                                       std::forward<Args>(args)...);
}

template<typename... Args>
bool EmitSignal(const std::string &object_path,
                const std::string &interface_name,
                const std::string &signal_name,
                Args &&... args) {
  DBusClient client;
  return client.EmitSignal(object_path, interface_name, signal_name, std::forward<Args>(args)...);
}

}  // namespace enckit
}  // namespace kviolet

#endif  ///__KVIOLET__ENCKIT__DBUS__CLIENT__H__
