#ifndef __KVIOLET__ENCKIT__DBUS__SERVER__H__
#define __KVIOLET__ENCKIT__DBUS__SERVER__H__

#include <glog/logging.h>
#include <sdbus-c++/sdbus-c++.h>

#include <memory>
#include <mutex>
#include <string>
namespace kviolet {
namespace enckit {

class DBusServer {
 public:
  explicit DBusServer(const std::string &name);
  virtual ~DBusServer();

 public:
  template<typename _Function>
  bool RegisterMethod(const std::string &method_name,
                      const std::string &interface_name,
                      const std::string &object_path,
                      _Function &&method) {
    if (object_.find(object_path) == object_.end()) {
      LOG(INFO) << "begin to create dbus object: " << object_path;
      object_.insert({object_path, std::move(sdbus::createObject(*connection_, object_path))});
    }

    LOG(INFO) << "begin to register method " << method_name << " on interface: " << interface_name;

    try {
      object_[object_path]->registerMethod(method_name).onInterface(interface_name).implementedAs(std::forward<_Function>(
          method));
    } catch (const std::exception &e) {
      LOG(ERROR) << "RegisterMethod failed:" << e.what();
      return false;
    }

    return true;
  }

  template<typename _Signal>
  bool RegisterSignal(const std::string &signal_name,
                      const std::string &interface_name,
                      const std::string &object_path) {
    if (object_.find(object_path) == object_.end()) {
      LOG(INFO) << "begin to create object: " << object_path;
      object_.insert({object_path, std::move(sdbus::createObject(*connection_, object_path))});
    }

    LOG(INFO) << "begin to register signal " << signal_name << " on interface: " << interface_name;

    try {
      object_[object_path]->registerSignal(signal_name).onInterface(interface_name).withParameters<_Signal>();
    } catch (const std::exception &e) {
      LOG(ERROR) << "RegisterSignal failed:" << e.what();
      return false;
    }

    return true;
  }

 public:
  bool Initialize();
  bool Start();
  void Stop();
  void Destroy();
  void Service();

 private:
  std::string service_name_;
  std::unique_ptr<sdbus::IConnection> connection_;
  std::map<std::string, std::unique_ptr<sdbus::IObject>> object_;
};

}  // namespace enckit
}  // namespace kviolet

#endif  ///__KVIOLET__ENCKIT__DBUS__SERVER__H__
