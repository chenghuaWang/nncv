#include "nncv/vm/op/conv2d_x86.hpp"

namespace nncv {
namespace vm {
namespace op {

Shape<4> CalculateDstShapeAfterConv2d(int src_n, int src_c, int src_h, int src_w, int k, int stride,
                                      int padding, int dilation) {
  int dilation_eq_kernel = k + (k - 1) * (dilation - 1);
  int h = (src_h - dilation_eq_kernel + 2 * padding) / stride + 1;
  int w = (src_w - dilation_eq_kernel + 2 * padding) / stride + 1;
  return MakeShape4D<4>(src_n, src_c, h, w);
}

void conv2d_naive_x86(float* src, float* dst, float* kernel, const TensorDataLayoutType& layout,
                      int src_n, int src_c, int src_h, int src_w, int k, int stride, int padding,
                      int dilation) {
  // TODO
}

void conv2d_img2col_x86(float* src, float* dst, float* kernel, const TensorDataLayoutType& layout,
                        int src_n, int src_c, int src_h, int src_w, int k, int stride, int padding,
                        int dilation) {
  // TODO
}

void conv2d_winograd_x86(float* src, float* dst, float* kernel, const TensorDataLayoutType& layout,
                         int src_n, int src_c, int src_h, int src_w, int k, int stride, int padding,
                         int dilation) {
  // TODO
}

void Conv2dX86(float* src, float* dst, float* kernel, const TensorDataLayoutType& layout, int src_n,
               int src_c, int src_h, int src_w, int k, int stride, int padding, int dilation,
               bool deterministic) {
  // TODO
}

}  // namespace op
}  // namespace vm
}  // namespace nncv