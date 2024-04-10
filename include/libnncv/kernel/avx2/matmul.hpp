/**
 * @file matmul.hpp
 * @author Chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef NNCV_LIB_NNCV_RT_AVX2_MATMUL_
#define NNCV_LIB_NNCV_RT_AVX2_MATMUL_

#include <Eigen/Dense>
#include "libnncv/DataType.hpp"

namespace nncv::rt {
namespace kernel {

// export to mlir's func
extern "C" {
void avx2_gemm_f32(MemRefDescriptor<float, 2> lhs, MemRefDescriptor<float, 2> rhs,
                   MemRefDescriptor<float, 2> dst);
}

void __gemm_f32(Eigen::MatrixXf& lhs, Eigen::MatrixXf& rhs, Eigen::MatrixXf& dst);

}  // namespace kernel
}  // namespace nncv::rt

#endif  //! NNCV_LIB_NNCV_RT_AVX2_MATMUL_