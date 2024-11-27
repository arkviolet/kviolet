#include "plug_instance.h"

#include <iostream>

bool PlugInstance::OnInitialize() {
  std::cout << "PlugInstance::OnInitialize" << std::endl;
  return true;
}

void PlugInstance::OnDestroy() {
  std::cout << "PlugInstance::OnDestroy" << std::endl;
}

bool PlugInstance::OnStart() {
  std::cout << "PlugInstance::OnStart" << std::endl;
  return true;
}

void PlugInstance::OnStop() {
  std::cout << "PlugInstance::OnStop" << std::endl;
}
