#ifndef NNCV_VM_UTILS_HPP
#define NNCV_VM_UTILS_HPP

#ifdef NNCV_ENABLE_CUDA
#include "nncv/vm/cuda/vm_utils_cuda.cuh"
#endif

#include "nncv/core/base.hpp"

namespace nncv {
namespace vm {
void DebugPrintDeviceInfo();
}
}  // namespace nncv

#endif  // NNCV_VM_UTILS_HPP