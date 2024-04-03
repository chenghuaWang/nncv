#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/Operation.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"
#include "nncv/compiler/Dialects/AutoTen/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"

namespace mlir::nncv::aten {

namespace {

bool isInAffineForScope(mlir::Operation* op) {
  mlir::Operation* top = op->getParentOp();
  while (top) {
    if (mlir::isa<mlir::affine::AffineForOp>(top)) { return true; }
    top = top->getParentOp();
  }
  return false;
}

class MemrefLoadToAffineLoardPattern final : public mlir::OpRewritePattern<mlir::memref::LoadOp> {
 public:
  using OpRewritePattern::OpRewritePattern;
  mlir::LogicalResult matchAndRewrite(mlir::memref::LoadOp op,
                                      mlir::PatternRewriter& rewriter) const override {
    if (isInAffineForScope(op)) {
      if (op.getIndices().empty()) {
        rewriter.replaceOpWithNewOp<mlir::affine::AffineLoadOp>(op,
                                                                /*memref*/ op.getMemRef());
      } else {
        rewriter.replaceOpWithNewOp<mlir::affine::AffineLoadOp>(op,
                                                                /*memref*/ op.getMemRef(),
                                                                /*indicies*/ op.getIndices());
      }
      return mlir::LogicalResult::success();
    } else {
      return mlir::LogicalResult::failure();
    }
    return mlir::LogicalResult::failure();
  }
};

class MemrefStoreToAffineStorePattern final : public mlir::OpRewritePattern<mlir::memref::StoreOp> {
 public:
  using OpRewritePattern::OpRewritePattern;
  mlir::LogicalResult matchAndRewrite(mlir::memref::StoreOp op,
                                      mlir::PatternRewriter& rewriter) const override {
    if (isInAffineForScope(op)) {
      rewriter.replaceOpWithNewOp<mlir::affine::AffineStoreOp>(
          op,
          /*value to store*/ op.getValueToStore(), /*Memref*/ op.getMemRef(),
          /*indicies*/ op.getIndices());
      return mlir::LogicalResult::success();
    } else {
      return mlir::LogicalResult::failure();
    }
    return mlir::LogicalResult::failure();
  }
};

class RaiseMemerefLSInAffineToAffineLSPass final
    : public RaiseMemerefLSInAffineToAffineLSBase<RaiseMemerefLSInAffineToAffineLSPass> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::affine::AffineDialect, mlir::memref::MemRefDialect,
                    mlir::aten::AtenDialect>();
    return;
  }

  void runOnOperation() override {
    mlir::MLIRContext* context = &getContext();
    mlir::RewritePatternSet patterns(context);

    // insert rewrite patternt
    patterns.insert<MemrefLoadToAffineLoardPattern, MemrefStoreToAffineStorePattern>(context);

    // do rewrite
    if (mlir::failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      return;
    }
    return;
  };
};

}  // namespace

std::unique_ptr<mlir::Pass> createRaiseMemerefLSInAffineToAffineLSPass() {
  return std::make_unique<RaiseMemerefLSInAffineToAffineLSPass>();
}

}  // namespace mlir::nncv::aten