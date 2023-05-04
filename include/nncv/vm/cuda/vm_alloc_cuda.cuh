#ifndef NNCV_VM_ALLOC_CUDA_CUH
#define NNCV_VM_ALLOC_CUDA_CUH

#include "nncv/vm/cuda/vm_cuda_error.cuh"

namespace nncv {
namespace vm {

extern "C" void _VmCudaMallocWarper(void** _devPtr, size_t _size);

extern "C" void _VmCudaFreeWarper(void* _devPtr);

}  // namespace vm
}  // namespace nncv

#endif