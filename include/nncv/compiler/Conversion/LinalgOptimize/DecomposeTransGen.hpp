#ifndef NNCV_C_CONVERSION_LINALG_DECOMPOSE_TRANS_GEN_HPP_
#define NNCV_C_CONVERSION_LINALG_DECOMPOSE_TRANS_GEN_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_DECOMPOSETRANSFORMGEN
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createDecomposeTransformGenPass();
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_LINALG_DECOMPOSE_TRANS_GEN_HPP_