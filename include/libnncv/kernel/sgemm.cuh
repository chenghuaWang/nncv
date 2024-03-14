#ifndef LIBNNCV_KERNEL_SGEMM_CUH_
#define LIBNNCV_KERNEL_SGEMM_CUH_

#include "cuda_runtime.h"

namespace nncv {
namespace rt {
namespace kernel {

#define BLOCK_SIZE_M 128
#define BLOCK_SIZE_K 8
#define BLOCK_SIZE_N 128
#define THREAD_SIZE_X 8
#define THREAD_SIZE_Y 8

// The single precision Gemm
//
__global__ void sgemm(float* __restrict__ lhs, float* __restrict__ rhs, float* __restrict__ dst,
                      int m, int n, int k);

}  // namespace kernel
}  // namespace rt
}  // namespace nncv

#endif  //! LIBNNCV_KERNEL_SGEMM_CUH_