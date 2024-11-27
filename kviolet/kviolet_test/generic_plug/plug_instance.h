#pragma once

#include <functional>
#include <memory>

#include "../../source/kviolet.h"

using namespace kviolet::module;

class PlugInstance final : public PlugBase {
 public:
  STATIC_PLUG_INSTANCE_CREATE(PlugInstance);

 public:
  PlugInstance() = default;
  ~PlugInstance() = default;

 protected:
  bool OnInitialize() override;
  void OnDestroy() override;
  bool OnStart() override;
  void OnStop() override;
};

STATIC_PLUG_INSTANCE_REGISTER("PlugInstance", PlugInstance::Create)
