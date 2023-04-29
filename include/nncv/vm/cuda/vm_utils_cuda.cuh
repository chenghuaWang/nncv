#ifndef NNCV_VM_UTILS_CUDA_CUH
#define NNCV_VM_UTILS_CUDA_CUH

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

namespace nncv {
namespace vm {

extern "C" void PrintCudaDevicesInfo();

}  // namespace vm
}  // namespace nncv

#endif  // NNCV_VM_UTILS_CUDA_CUH