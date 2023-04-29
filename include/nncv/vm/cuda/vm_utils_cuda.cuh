#ifndef NNCV_VM_UTILS_CUDA_CUH
#define NNCV_VM_UTILS_CUDA_CUH

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "nncv/core/common/data_types.hpp"

namespace nncv {
namespace vm {

extern "C" void PrintCudaDevicesInfo();

extern "C" void GetCudaDeviceProperty(CudaDeviceProperty_t& cdp, int idx = 0);

}  // namespace vm
}  // namespace nncv

#endif  // NNCV_VM_UTILS_CUDA_CUH