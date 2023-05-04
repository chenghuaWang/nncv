#include "nncv/vm/cuda/vm_alloc_cuda.cuh"

namespace nncv {
namespace vm {

extern "C" void _VmCudaMallocWarper(void** _devPtr, size_t _size) {
  NNCV_CUDA_CALL(cudaMalloc(_devPtr, _size));
}

extern "C" void _VmCudaFreeWarper(void* _devPtr) { NNCV_CUDA_CALL(cudaFree(_devPtr)); }

}  // namespace vm
}  // namespace nncv