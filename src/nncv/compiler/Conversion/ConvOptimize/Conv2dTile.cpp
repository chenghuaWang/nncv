// check https://discourse.llvm.org/t/vectorization-of-convolution-op/60458/7 as a reference
#include "nncv/compiler/Conversion/ConvOptimize/Conv2dTile.hpp"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/LinalgInterfaces.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/IR/Operation.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_CONV2DTILE
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

void tileAndReplcae(IRRewriter& rewriter, mlir::Operation* op, llvm::SmallVector<int64_t> sizes) {
  linalg::LinalgTilingOptions tileOption;
  tileOption.setTileSizes(sizes);

  OpBuilder::InsertionGuard guard(rewriter);
  rewriter.setInsertionPoint(op);

  auto tiledOps =
      linalg::tileLinalgOp(rewriter, mlir::cast<mlir::linalg::LinalgOp>(op), tileOption);
  rewriter.replaceOp(op, tiledOps->tensorResults);
}

class Conv2dTilePass : public impl::Conv2dTileBase<Conv2dTilePass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    llvm::SmallVector<mlir::Operation*> candidates;
    IRRewriter rewriter(&getContext());
    getOperation()->walk([&](mlir::linalg::LinalgOp op) {
      if (mlir::linalg::isaConvolutionOpInterface(op)) candidates.emplace_back(op);
    });

    // tile to one dims;
    for (auto item : candidates) {
      auto op = mlir::cast<mlir::linalg::LinalgOp>(item);

      if (mlir::isa<mlir::linalg::Conv2DNhwcHwcfOp>(op)) {
        tileAndReplcae(rewriter, op, {0, 1, 8, 8, 1});
        continue;
      }

      // TODO
      // others layout / pooling
    }

    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::populateDecomposeConvolutionPatterns(patterns);
      mlir::linalg::populateLinalgTilingCanonicalizationPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createConv2dTilePass() { return std::make_unique<Conv2dTilePass>(); }
}  // namespace mlir::nncv