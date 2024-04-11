/**
 * @file conv2d.hpp
 * @author Chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef NNCV_LIB_NNCV_RT_AVX2_CONV2D_
#define NNCV_LIB_NNCV_RT_AVX2_CONV2D_

#include "libnncv/DataType.hpp"

namespace nncv::rt {
namespace kernel {

extern "C" {
void avx2_conv2d_f32();
}

void __conv2d_f32(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C, int IH, int IW,
                  int F, int KH, int KW, int SH, int SW, int DH, int DW, int OH, int OW);

void __conv2d_img2col_f32(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C, int IH,
                          int IW, int F, int KH, int KW, int SH, int SW, int DH, int DW, int OH,
                          int OW);

void __conv2d_winograd_3x3_f32(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C,
                               int IH, int IW, int F, int KH, int KW, int SH, int SW, int DH,
                               int DW, int OH, int OW);

void __conv2d_implicit_gemm_f32(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C,
                                int IH, int IW, int F, int KH, int KW, int SH, int SW, int DH,
                                int DW, int OH, int OW);

void __conv2d_raw(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C, int IH, int IW,
                  int F, int KH, int KW, int SH, int SW, int DH, int DW, int OH, int OW);

}  // namespace kernel
}  // namespace nncv::rt

#endif  //! NNCV_LIB_NNCV_RT_AVX2_CONV2D_