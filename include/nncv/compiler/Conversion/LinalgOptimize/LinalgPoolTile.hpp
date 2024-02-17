#ifndef NNCV_C_CONVERSION_LINALG_POOLING_TILE_HPP_
#define NNCV_C_CONVERSION_LINALG_POOLING_TILE_HPP_

#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/SCF/Transforms/TileUsingInterface.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_LINALGPOOLINGTILE
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {

namespace {

llvm::SmallVector<scf::ForOp> toScfForOp(llvm::SmallVector<mlir::Operation*, 8>& ops);

FailureOr<mlir::scf::SCFTilingResult> tileAndReplacePoolOp(IRRewriter& rewriter,
                                                           mlir::Operation* op,
                                                           llvm::SmallVector<int64_t> sizes);
}  // namespace

std::unique_ptr<mlir::Pass> createLinalgPoolingTilePass(bool flag = false);
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_CONVERSION_LINALG_POOLING_TILE_HPP_