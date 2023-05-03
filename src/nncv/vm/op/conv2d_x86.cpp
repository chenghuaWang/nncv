#include "nncv/vm/op/conv2d_x86.hpp"

namespace nncv {
namespace vm {
namespace op {

Shape CalculateDstShapeAfterConv2d(int src_n, int src_c, int src_h, int src_w, int c_out, int k,
                                   int stride, int padding, int dilation) {
  int dilation_eq_kernel = k + (k - 1) * (dilation - 1);
  int h = (src_h - dilation_eq_kernel + 2 * padding) / stride + 1;
  int w = (src_w - dilation_eq_kernel + 2 * padding) / stride + 1;
  return Shape(src_n, c_out, h, w);
}

template<typename T>
void conv2d_naive_x86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
                      const TensorDataLayoutType& layout, int in_channel, int out_channel, int k,
                      int stride, int padding, int dilation) {
  // TODO
}

template<typename T>
void conv2d_img2col_x86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
                        const TensorDataLayoutType& layout, int in_channel, int out_channel, int k,
                        int stride, int padding, int dilation) {
  // TODO
}

template<typename T>
void conv2d_winograd_x86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
                         const TensorDataLayoutType& layout, int in_channel, int out_channel, int k,
                         int stride, int padding, int dilation) {
  // TODO
}

template<typename T>
void Conv2dX86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
               const TensorDataLayoutType& layout, int in_channel, int out_channel, int k,
               int stride, int padding, int dilation, bool deterministic) {
  // TODO
}

}  // namespace op
}  // namespace vm
}  // namespace nncv