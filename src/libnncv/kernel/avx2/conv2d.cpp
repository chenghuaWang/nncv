#include "libnncv/kernel/avx2/conv2d.hpp"
#include <unsupported/Eigen/CXX11/Tensor>

namespace nncv::rt {
namespace kernel {

void __conv2d_f32(Eigen::Map<Eigen::MatrixXf>& input, Eigen::Map<Eigen::MatrixXf>& kernel,
                  Eigen::Map<Eigen::MatrixXf>& output, int kern_w, int kern_h, int stirde_w,
                  int stride_h, int dilation_w, int dilation_h) {}

}  // namespace kernel
}  // namespace nncv::rt