#include "nncv/vm/vm_utils.hpp"

namespace nncv {
namespace vm {

void DebugPrintDeviceInfo() {
#ifdef NNCV_ENABLE_CUDA
  PrintCudaDevicesInfo();
#endif
}

void GetHostDeviceProperty(HostDeviceProperty_t& hdp) {
  // TODO
}

}  // namespace vm
}  // namespace nncv