#ifndef __KVIOLET__MODULE__PLUG_BASE_FACTORY_H__
#define __KVIOLET__MODULE__PLUG_BASE_FACTORY_H__

#include <functional>
#include <memory>
#include <string>

#include "plug_base.h"

#define REGISTER_PLUG_PRIORITY (2100)
#define STATIC_PLUG_INSTANCE_CREATE(class_name)   \
  static std::shared_ptr<class_name> Create() {   \
    auto handle = std::make_shared<class_name>(); \
    return handle;                                \
  }

#define STATIC_PLUG_INSTANCE_REGISTER(class_name, func)                                                \
  static void STATIC_REGISTER##_class_name(void) __attribute__((constructor(REGISTER_PLUG_PRIORITY))); \
  static void STATIC_REGISTER##_class_name(void) {                                                     \
    kviolet::module::RegisterPlugFactory(class_name, func);                                            \
  }

namespace kviolet {
namespace module {

void RegisterPlugFactory(const std::string& plug_name, const std::function<std::shared_ptr<PlugBase>()>& plug);

std::shared_ptr<PlugBase> LoadDriver(const std::string& driver_path, const std::string& driver_name);

}  // namespace module
}  // namespace kviolet

#endif  ///__KVIOLET__MODULE__PLUG_BASE_FACTORY_H__
