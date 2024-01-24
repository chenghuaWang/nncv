#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include "nncv/compiler/Dialects/AutoTen/IR/AtenDialect.hpp"
#include "nncv/compiler/Dialects/AutoTen/IR/AtenTypes.hpp"
#include "nncv/compiler/Dialects/AutoTen/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/AutoTen/Transforms/Passes.hpp"

namespace mlir::nncv::aten {

namespace {

class EliminateStoreLoadForScfPattern final : public mlir::OpRewritePattern<mlir::arith::ExtUIOp> {
 public:
  using OpRewritePattern::OpRewritePattern;

  mlir::LogicalResult matchAndRewrite(mlir::arith::ExtUIOp op,
                                      mlir::PatternRewriter& rewriter) const override {
    mlir::Operation* memAllocaOp = nullptr;
    mlir::Operation* memStoreOp = nullptr;
    if (op->getNextNode() && mlir::isa<mlir::memref::AllocaOp>(op->getNextNode())) {
      memAllocaOp = op->getNextNode();
    } else {
      return mlir::failure();
    }
    if (memAllocaOp->getNextNode()
        && mlir::isa<mlir::memref::StoreOp>(memAllocaOp->getNextNode())) {
      memStoreOp = memAllocaOp->getNextNode();
    } else {
      return mlir::failure();
    }
    if (memStoreOp->getNextNode() && mlir::isa<mlir::scf::ConditionOp>(memStoreOp->getNextNode())) {
      rewriter.eraseOp(memStoreOp);
      rewriter.eraseOp(memAllocaOp);
      rewriter.eraseOp(op);
      return mlir::success();
    } else {
      return mlir::failure();
    }
    return mlir::failure();
  }
};

class EliminateRedundantLoadStoreForScfConditional
    : public EliminateRedundantLoadStoreForScfConditionalBase<
          EliminateRedundantLoadStoreForScfConditional> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::arith::ArithDialect, mlir::memref::MemRefDialect>();
    return;
  }

  void runOnOperation() override {
    mlir::MLIRContext* context = &getContext();
    mlir::RewritePatternSet patterns(context);

    // insert rewrite patternt
    patterns.insert<EliminateStoreLoadForScfPattern>(context);

    // do rewrite
    if (mlir::failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      return;
    }

    return;
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createEliminateRedundantLoadStoreForScfConditionalPass() {
  return std::make_unique<EliminateRedundantLoadStoreForScfConditional>();
}
}  // namespace mlir::nncv::aten