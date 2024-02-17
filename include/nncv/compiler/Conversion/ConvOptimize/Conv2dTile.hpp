#ifndef NNCV_C_CONVERSION_CONV2d_TILE_ALL_
#define NNCV_C_CONVERSION_CONV2d_TILE_ALL_

#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/SCF/Transforms/TileUsingInterface.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_CONV2DTILE
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {
std::unique_ptr<mlir::Pass> createConv2dTilePass();

namespace {
llvm::SmallVector<scf::ForOp> toScfForOp(llvm::SmallVector<mlir::Operation*, 8>& ops);

FailureOr<mlir::scf::SCFTilingResult> tileAndReplaceConvOp(IRRewriter& rewriter,
                                                           mlir::Operation* op,
                                                           llvm::SmallVector<int64_t> sizes);
}  // namespace

}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_CONV2d_TILE_ALL_