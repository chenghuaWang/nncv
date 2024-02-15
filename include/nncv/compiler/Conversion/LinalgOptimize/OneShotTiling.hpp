#ifndef NNCV_C_CONVERSION_LINALG_ONESHOTTILING_HPP_
#define NNCV_C_CONVERSION_LINALG_ONESHOTTILING_HPP_

#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_ONESHOTTILING
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {

namespace {}

std::unique_ptr<mlir::Pass> createOneShotTilingPass();

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_LINALG_ONESHOTTILING_HPP_