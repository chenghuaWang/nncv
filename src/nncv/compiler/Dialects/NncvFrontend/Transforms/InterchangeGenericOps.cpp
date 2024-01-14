#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Linalg/Utils/Utils.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir::nncv {

namespace {
class GenericOpInterchangePattern : public mlir::OpRewritePattern<mlir::linalg::GenericOp> {
 public:
  using OpRewritePattern<mlir::linalg::GenericOp>::OpRewritePattern;

  LogicalResult matchAndRewrite(linalg::GenericOp genericOp,
                                PatternRewriter& rewriter) const override {
    llvm::SmallVector<unsigned> interchange;

    auto canInterchange = false;
    auto numParallelLoop = genericOp.getNumParallelLoops();

    if (numParallelLoop == 0) { return mlir::failure(); }
    for (auto iter : llvm::enumerate(genericOp.getIteratorTypesArray())) {
      if (linalg::isParallelIterator(iter.value())) {
        interchange.push_back(iter.index());
        if (iter.index() >= numParallelLoop) { canInterchange = true; }
      }
    }

    if (!canInterchange) { return mlir::failure(); }
    for (auto iter : llvm::enumerate(genericOp.getIteratorTypesArray())) {
      if (linalg::isReductionIterator(iter.value())) { interchange.push_back(iter.index()); }
    }

    return interchangeGenericOp(rewriter, genericOp, interchange);
  }
};

class InterchangeGenericOpsPass : public InterchangeGenericOpsBase<InterchangeGenericOpsPass> {
  void getDependentDialects(DialectRegistry& registry) const override {
    registry.insert<linalg::LinalgDialect>();
  }

  void runOnOperation() override {
    RewritePatternSet patterns(&getContext());
    patterns.add<GenericOpInterchangePattern>(&getContext());
    if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      return signalPassFailure();
    }
  }
};
}  // namespace

std::unique_ptr<mlir::Pass> createInterchangeGenericOpsPass() {
  return std::make_unique<InterchangeGenericOpsPass>();
}
}  // namespace mlir::nncv
