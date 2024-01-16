#ifndef NNCV_C_CONVERSION_CONV2D_OPTIMIZE_WINOGRAD_
#define NNCV_C_CONVERSION_CONV2D_OPTIMIZE_WINOGRAD_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_OPTIMIZECONV2DUSINGWINOGRAD
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createOptimizeConv2dUsingWinogradPass();

}  // namespace nncv
}  // namespace mlir

namespace mlir::nncv::winograd {
// Values from
// Liu, J. et al (2021) Optimizing Winograd-Based Convolution with Tensor Cores.
// https://dl.acm.org/doi/abs/10.1145/3472456.3472473
// clang-format off
    const float BT_6x6_3x3[] = {
  1,      0, -21./4.,        0,  21./4.,       0, -1, 0,
  0,      1,       1,  -17./4., -17./4.,       1,  1, 0,
  0,     -1,       1,   17./4., -17./4.,      -1,  1, 0,
  0,   1./2,   1./4.,   -5./2.,  -5./4.,       2,  1, 0,
  0,  -1./2,   1./4.,    5./2.,  -5./4.,      -2,  1, 0,
  0,      2,       4,   -5./2.,      -5,   1./2.,  1, 0,
  0,     -2,       4,    5./2.,      -5,  -1./2.,  1, 0,
  0,     -1,       0,   21./4.,       0, -21./4.,  0, 1
};

const float B_6x6_3x3[] = {
        1,       0,       0,      0,      0,      0,      0,       0,
        0,       1,      -1,   1./2,  -1./2,      2,     -2,      -1,
  -21./4.,       1,       1,  1./4.,  1./4.,      4,      4,       0,
        0, -17./4.,  17./4., -5./2.,  5./2., -5./2.,  5./2.,  21./4.,
   21./4., -17./4., -17./4., -5./4., -5./4.,     -5,     -5,       0,
        0,       1,      -1,      2,     -2,  1./2., -1./2., -21./4.,
       -1,       1,       1,      1,      1,      1,      1,       0,
        0,       0,       0,      0,      0,      0,      0,       1
};

const float G_6x6_3x3[] = {
       1,       0,      0,
  -2./9.,  -2./9., -2./9.,
  -2./9.,   2./9., -2./9.,
   1./90,   1./45,  2./45,
   1./90,  -1./45,  2./45,
  32./45,  16./45,  8./45,
  32./45, -16./45,  8./45,
       0,       0,      1
};

const float AT_6x6_3x3[] = {
  1,  1,   1,   1,    1,     1,      1,  0,
  0,  1,  -1,   2,   -2,  1./2,  -1./2,  0,
  0,  1,   1,   4,    4,  1./4,   1./4,  0,
  0,  1,  -1,   8,   -8,  1./8,  -1./8,  0,
  0,  1,   1,  16,   16, 1./16,  1./16,  0,
  0,  1,  -1,  32,  -32, 1./32, -1./32,  1
};

const float A_6x6_3x3[] = {
  1,     0,    0,     0,     0,      0,
  1,     1,    1,     1,     1,      1,
  1,    -1,    1,    -1,     1,     -1,
  1,     2,    4,     8,    16,     32,
  1,    -2,    4,    -8,    16,    -32,
  1,  1./2, 1./4,  1./8, 1./16,  1./32,
  1, -1./2, 1./4, -1./8, 1./16, -1./32,
  0,     0,    0,     0,     0,      1
};
// clang-format on

}  // namespace mlir::nncv::winograd

#endif  //! NNCV_C_CONVERSION_CONV2D_OPTIMIZE_WINOGRAD_