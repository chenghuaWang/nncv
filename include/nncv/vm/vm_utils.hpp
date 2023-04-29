#ifndef NNCV_VM_UTILS_HPP
#define NNCV_VM_UTILS_HPP

#ifdef NNCV_ENABLE_CUDA
#include "nncv/vm/cuda/vm_utils_cuda.cuh"
#endif

#include "nncv/core/base.hpp"
#include "nncv/core/common/data_types.hpp"

namespace nncv {
namespace vm {

void DebugPrintDeviceInfo();

void GetHostDeviceProperty(HostDeviceProperty_t& hdp);

}  // namespace vm
}  // namespace nncv

#endif  // NNCV_VM_UTILS_HPP