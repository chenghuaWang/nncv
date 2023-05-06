#include "nncv/vm/vm.hpp"
#include "nncv/core/common/tensor.hpp"

#include "nncv/vm/io/image.hpp"

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

int main() {
  nncv::vm::DebugPrintDeviceInfo();
  // For testing Convolution
  // nncv::Tensor image = nncv::vm::io::ImageRead("ikun.jpg");
  // image << 9.0 << 12.0;
  // image.to("cuda: 0");
  // nncv::Tensor x(1, 3, 192, 192, NNCV_FLOAT32);
  // x.to("cuda: 0");
  // nncv::Tensor kernel(3, 3, 3, 3, NNCV_FLOAT32);
  // nncv::Tensor bias(3, 3, sizeof(float));
  // nncv::vm::op::conv2d_naive_x86<float>(image, x, kernel, bias, nncv::kNCHW, 3, 3, 3, 3, 1, 1, 2,
  // 2);
}