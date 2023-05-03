#ifndef NNCV_CONV2D_X86_HPP
#define NNCV_CONV2D_X86_HPP

#include "nncv/core/common/tensor.hpp"

#if defined(NNCV_HAVE_SSE) || defined(NNCV_HAVE_AVX2) || defined(NNCV_HAVE_AVX512)
#include <immintrin.h>
#endif

/**
 * For Convolution operator impl. There is no need to consider about padding, memory re-alloc for
 * padding is already done before Convolution operator. The most common workflow is shown below:
 *
 * Padding(if has) -> Convolution -> BatchNorm -> ReLU, or
 * Padding(if has) -> Convolution+BatchNorm+ReLU(fused).
 *
 * !!! Remember, VM's memory manager plays quite vital role in padding operator !!!
 * For example, if there is a expression: Out = Conv(A * B), and this Conv has padding. When
 * executing, A * B will store to a Temp Tensor, And This Temp Tensor will be alloced as the size
 * that already padded. This optimization will avoid no necessary memory allocation and transfer.
 * So, if VM involved in, there is no need to request VM memory manager to alloc another memory and
 * transfer memory from old to new.
 *
 */

namespace nncv {
namespace vm {
namespace op {

Shape CalculateDstShapeAfterConv2d(int src_n, int src_c, int src_h, int src_w, int c_out, int k,
                                   int stride, int padding, int dilation);

template<typename T>
void conv2d_naive_x86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
                      const TensorDataLayoutType& layout, int in_channel, int out_channel, int k,
                      int stride, int padding, int dilation);
template<typename T>
void conv2d_img2col_x86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
                        const TensorDataLayoutType& layout, int in_channel, int out_channel, int k,
                        int stride, int padding, int dilation);
template<typename T>
void conv2d_winograd_x86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
                         const TensorDataLayoutType& layout, int in_channel, int out_channel, int k,
                         int stride, int padding, int dilation);
template<typename T>
void Conv2dX86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
               const TensorDataLayoutType& layout, int in_channel, int out_channel, int k,
               int stride, int padding, int dilation, bool deterministic);

}  // namespace op
}  // namespace vm
}  // namespace nncv

#endif  //! NNCV_CONV2D_X86_HPP