#include "nncv/vm/vm_utils.hpp"

namespace nncv {
namespace vm {

void DebugPrintDeviceInfo() {
#ifdef NNCV_ENABLE_CUDA
  PrintCudaDevicesInfo();
#endif
}

}  // namespace vm
}  // namespace nncv