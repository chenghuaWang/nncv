#include "nncv/vm/vm.hpp"

VirtualMachine::~VirtualMachine() {
  // TODO before delete all device, make sure all memory on those device is released.
  delete m_DevicePool;
}

bool VirtualMachine::Init() {
  // 1. init the device pool, check the running environment
  m_DevicePool = new nncv::DevicePool();
  m_DevicePool->RegisterDevice(nncv::kHost);
#ifdef NNCV_ENABLE_CUDA

#endif
  return true;
}

int main() { nncv::vm::DebugPrintDeviceInfo(); }