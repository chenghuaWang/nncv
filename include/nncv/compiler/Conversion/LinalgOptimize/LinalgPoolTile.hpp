#ifndef NNCV_C_CONVERSION_LINALG_POOLING_TILE_HPP_
#define NNCV_C_CONVERSION_LINALG_POOLING_TILE_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_LINALGPOOLINGTILE
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createLinalgPoolingTilePass(bool flag = false);
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_LINALG_POOLING_TILE_HPP_