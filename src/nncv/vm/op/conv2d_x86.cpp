#include "nncv/vm/op/conv2d_x86.hpp"
#include <vector>

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
                      const TensorDataLayoutType& layout, int in_channel, int out_channel, int k_h,
                      int k_w, int stride_h, int stride_w, int dilation_h, int dilation_w) {
  const int batch_size = src.GetConstShape().n;
  const int in_w = src.GetConstShape().w;

  const int out_h = dst.GetConstShape().h;
  const int out_w = dst.GetConstShape().w;

  const bool has_bias = bias.Empty();

  const int kernel_size = k_h * k_w;

  // calculate kernel's offset.
  // VLA is not necessary, why not use vector to make live easier :-)
  std::vector<int> kernel_offsets(kernel_size);
  int* kernel_offsets_ptr = &kernel_offsets[0];
  {
    int ptr_1 = 0;
    int ptr_2 = 0;
    int gap = in_w * dilation_h - k_w * dilation_w;
    for (int i = 0; i < k_h; ++i) {
      for (int j = 0; j < k_w; ++j) {
        kernel_offsets_ptr[ptr_1] = ptr_2;
        ptr_1++;
        ptr_2 += dilation_w;
      }
      ptr_2 += gap;
    }
  }

  // conv it !
  // bias outside of for loop.
  if (has_bias) {
#pragma omp parallel for num_threads()  // TODO nums
    for (int batch = 0; batch < batch_size; ++batch) {
      for (int per_out_channel = 0; per_out_channel < out_channel; ++per_out_channel) {
        T* dst_ptr = dst.GetChannelPtrOn4Dims<T>(batch, per_out_channel);
        for (int per_h = 0; per_h < out_h; ++per_h) {
          for (int per_w = 0; per_w < out_w; ++per_w) {
            T sum = bias.at<T>(per_out_channel);
            const T* kernel_ptr = (const T*)kernel + kernel_size * in_channel * per_out_channel;
            for (int per_in_channel = 0; per_in_channel < in_channel; ++per_in_channel) {
              const T* src_block_ptr =
                  src.GetRowPtrOn4Dims<T>(batch, per_in_channel, per_h * stride_h)
                  + per_w * stride_w;
              for (int k = 0; k < kernel_size; ++k) {
                float val = src_block_ptr[kernel_offsets[k]];
                float wt = kernel_ptr[k];
                sum += val * wt;
              }
              kernel_ptr += kernel_size;
            }
            dst_ptr[per_w] = sum;
          }
          dst_ptr += out_w;
        }
      }
    }
  } else {
#pragma omp parallel for num_threads()  // TODO nums
  }
}

template<typename T>
void conv2d_img2col_x86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
                        const TensorDataLayoutType& layout, int in_channel, int out_channel,
                        int k_h, int k_w, int stride_h, int stride_w, int dilation_h,
                        int dilation_w) {
  // TODO
}

template<typename T>
void conv2d_winograd_x86(const Tensor& src, Tensor& dst, const Tensor& kernel, const Tensor& bias,
                         const TensorDataLayoutType& layout, int in_channel, int out_channel,
                         int k_h, int k_w, int stride_h, int stride_w, int dilation_h,
                         int dilation_w) {
  // TODO
}

}  // namespace op
}  // namespace vm
}  // namespace nncv