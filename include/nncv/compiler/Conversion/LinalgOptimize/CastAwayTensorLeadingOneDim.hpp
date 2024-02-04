#ifndef NNCV_C_CONVERSION_LINALG_CAST_AWAY_TENSOR_LEADING_ONE_DIM_HPP_
#define NNCV_C_CONVERSION_LINALG_CAST_AWAY_TENSOR_LEADING_ONE_DIM_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_LINALGOPCASTAWAYTENSORLEADINGONEDIM
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createLinalgOpCastAwayTensorLeadingOneDimPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_LINALG_CAST_AWAY_TENSOR_LEADING_ONE_DIM_HPP_