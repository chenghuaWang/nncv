/**
 * @file utils.cpp
 * @author Chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "libnncv/kernel/avx2/utils.hpp"
#include <Eigen/Core>

namespace nncv::rt {
namespace kernel::avx2 {

extern "C" void avx2_is_on() {
  printf("[ INFO ] is using backend instruction set: %s\n", Eigen::SimdInstructionSetsInUse());
}

}  // namespace kernel::avx2
}  // namespace nncv::rt