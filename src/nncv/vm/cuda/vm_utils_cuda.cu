#include "nncv/core/base.hpp"
#include "nncv/vm/cuda/vm_utils_cuda.cuh"

namespace nncv {
namespace vm {

extern "C" void PrintCudaDevicesInfo() {
  int device_cnt;
  cudaGetDeviceCount(&device_cnt);
  if ((device_cnt == 0 && nncv::is_cuda_builtin) || (nncv::is_cuda_builtin == 0)) {
    printf(
        "Error: This version of nncv is not build for cuda or your machine has no cuda device\n");
    exit(EXIT_CUDA_ERROR);
  }
  printf("Info: found cuda device %d\n", device_cnt);
}

extern "C" void GetCudaDeviceProperty(CudaDeviceProperty_t& cdp, int idx) {
  cudaDeviceProp device_prop;
  cudaGetDeviceProperties(&device_prop, idx);
  // TODO
}

}  // namespace vm
}  // namespace nncv
