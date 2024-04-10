/**
 * @file matmul.cpp
 * @author Chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "libnncv/kernel/avx2/matmul.hpp"

namespace nncv::rt {
namespace kernel {

void __gemm_f32(Eigen::Map<Eigen::MatrixXf>& lhs, Eigen::Map<Eigen::MatrixXf>& rhs,
                Eigen::Map<Eigen::MatrixXf>& dst) {
  dst = lhs * rhs;
}

extern "C" {
void avx2_gemm_f32(MemRefDescriptor<float, 2> lhs, MemRefDescriptor<float, 2> rhs,
                   MemRefDescriptor<float, 2> dst) {
  auto lhsRow = lhs.sizes[0];
  auto lhsCol = lhs.sizes[1];
  auto lhsDataPtr = lhs.allocated;
  auto rhsRow = rhs.sizes[0];
  auto rhsCol = rhs.sizes[1];
  auto rhsDataPtr = rhs.allocated;
  auto dstRow = dst.sizes[0];
  auto dstCol = dst.sizes[1];
  auto dstDataPtr = dst.allocated;

  // map to eigen
  auto _lhs_gemm_f32 = Eigen::Map<Eigen::MatrixXf>(lhsDataPtr, lhsRow, lhsCol);
  auto _rhs_gemm_f32 = Eigen::Map<Eigen::MatrixXf>(lhsDataPtr, lhsRow, lhsCol);
  auto _dst_gemm_f32 = Eigen::Map<Eigen::MatrixXf>(lhsDataPtr, lhsRow, lhsCol);

  __gemm_f32(_lhs_gemm_f32, _rhs_gemm_f32, _dst_gemm_f32);
}
}

}  // namespace kernel
}  // namespace nncv::rt