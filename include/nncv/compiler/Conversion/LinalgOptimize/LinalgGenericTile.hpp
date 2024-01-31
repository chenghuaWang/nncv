#ifndef NNCV_C_CONVERSION_LINALG_GENERIC_TILE_HPP_
#define NNCV_C_CONVERSION_LINALG_GENERIC_TILE_HPP_

#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_LINALGGENERICTILE
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createLinalgGenericTilePass(bool flag = false);
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_LINALG_GENERIC_TILE_HPP_