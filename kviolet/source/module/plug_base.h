#ifndef __KVIOLET__MODULE__PLUG_BASE_H__
#define __KVIOLET__MODULE__PLUG_BASE_H__

#include <iostream>
#include <map>
#include <string>

namespace kviolet {
namespace module {

typedef struct PlugBaseInfo {
  uint16_t pid;
  uint16_t vid;
  std::map<std::string, std::string> properties;

  std::string Properties(const std::string& key, const std::string& default_value = "") {
    auto find = properties.find(key);
    if (properties.end() == find) {
      return default_value;
    }
    return find->second;
  }
} PlugBaseInfo;

class PlugBase {
 public:
  PlugBase();
  virtual ~PlugBase();

 public:
  virtual bool Initialize(const PlugBaseInfo& info);
  virtual void Destroy();
  virtual bool Start();
  virtual void Stop();

 protected:
  virtual bool OnInitialize();
  virtual void OnDestroy();
  virtual bool OnStart();
  virtual void OnStop();

 protected:
  PlugBaseInfo plug_info_;
};

}  // namespace module
}  // namespace kviolet

#endif  ///__KVIOLET__MODULE__PLUG_BASE_H__
