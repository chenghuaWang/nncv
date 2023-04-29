#ifndef NNCV_CONV2D_X86_HPP
#define NNCV_CONV2D_X86_HPP

#include "nncv/core/common/tensor.hpp"

namespace nncv {
namespace vm {
namespace op {

Shape<4> CalculateDstShapeAfterConv2d(int src_n, int src_c, int src_h, int src_w, int k, int stride,
                                      int padding, int dilation);

void conv2d_naive_x86(float* src, float* dst, float* kernel, const TensorDataLayoutType& layout,
                      int src_n, int src_c, int src_h, int src_w, int k, int stride, int padding,
                      int dilation);

void conv2d_img2col_x86(float* src, float* dst, float* kernel, const TensorDataLayoutType& layout,
                        int src_n, int src_c, int src_h, int src_w, int k, int stride, int padding,
                        int dilation);

void conv2d_winograd_x86(float* src, float* dst, float* kernel, const TensorDataLayoutType& layout,
                         int src_n, int src_c, int src_h, int src_w, int k, int stride, int padding,
                         int dilation);

void Conv2dX86(float* src, float* dst, float* kernel, const TensorDataLayoutType& layout, int src_n,
               int src_c, int src_h, int src_w, int k, int stride, int padding, int dilation,
               bool deterministic);

}  // namespace op
}  // namespace vm
}  // namespace nncv

#endif  //! NNCV_CONV2D_X86_HPP