#include "plug_base.h"

namespace kviolet {
namespace module {

PlugBase::PlugBase() {}
PlugBase::~PlugBase() {}

bool PlugBase::Initialize(const PlugBaseInfo& info) {
  plug_info_ = info;
  return OnInitialize();
}

void PlugBase::Destroy() {
  OnDestroy();
}

bool PlugBase::Start() {
  return OnStart();
}

void PlugBase::Stop() {
  OnStop();
}

bool PlugBase::OnInitialize() {
  return true;
}

void PlugBase::OnDestroy() {}

bool PlugBase::OnStart() {
  return true;
}

void PlugBase::OnStop() {}

}  // namespace module
}  // namespace kviolet
