#ifndef NNCV_C_CONVERSION_LINALG_DECOMPOSE_TENSOR_CONCAT_HPP_
#define NNCV_C_CONVERSION_LINALG_DECOMPOSE_TENSOR_CONCAT_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_DECOMPOSETENSORCONCAT
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createDecomposeTensorConcatPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_LINALG_DECOMPOSE_TENSOR_CONCAT_HPP_