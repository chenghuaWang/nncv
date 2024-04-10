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

#include <Eigen/Dense>
#include "libnncv/DataType.hpp"

namespace nncv::rt {
namespace kernel {

void __conv2d_f32();

}  // namespace kernel
}  // namespace nncv::rt

#endif  //! NNCV_LIB_NNCV_RT_AVX2_CONV2D_