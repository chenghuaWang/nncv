#include "libnncv/kernel/avx2/conv2d.hpp"
#include <unsupported/Eigen/CXX11/Tensor>

namespace nncv::rt {
namespace kernel {

extern "C" {
void avx2_conv2d_f32() {}
}

void __conv2d_img2col_f32(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C, int IH,
                          int IW, int F, int KH, int KW, int SH, int SW, int DH, int DW, int OH,
                          int OW) {}

void __conv2d_winograd_3x3_f32(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C,
                               int IH, int IW, int F, int KH, int KW, int SH, int SW, int DH,
                               int DW, int OH, int OW) {}

void __conv2d_implicit_gemm_f32(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C,
                                int IH, int IW, int F, int KH, int KW, int SH, int SW, int DH,
                                int DW, int OH, int OW) {}

void __conv2d_raw(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C, int IH, int IW,
                  int F, int KH, int KW, int SH, int SW, int DH, int DW, int OH, int OW) {}

void __conv2d_f32(float* inputPtr, float* outputPtr, float* kernelPtr, int N, int C, int IH, int IW,
                  int F, int KH, int KW, int SH, int SW, int DH, int DW, int OH, int OW) {}

}  // namespace kernel
}  // namespace nncv::rt