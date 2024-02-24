#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/LoweringScfForAllToParallel.hpp"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlowOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/Passes.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_LOWERINGSCFFORALLTOPARALLEL
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

struct ForallLowering : public OpRewritePattern<mlir::scf::ForallOp> {
  using OpRewritePattern<mlir::scf::ForallOp>::OpRewritePattern;

  LogicalResult matchAndRewrite(mlir::scf::ForallOp forallOp,
                                PatternRewriter& rewriter) const override;
};

LogicalResult ForallLowering::matchAndRewrite(scf::ForallOp forallOp,
                                              PatternRewriter& rewriter) const {
  Location loc = forallOp.getLoc();
  if (!forallOp.getOutputs().empty())
    return rewriter.notifyMatchFailure(
        forallOp, "only fully bufferized scf.forall ops can be lowered to scf.parallel");

  // Convert mixed bounds and steps to SSA values.
  SmallVector<Value> lbs =
      getValueOrCreateConstantIndexOp(rewriter, loc, forallOp.getMixedLowerBound());
  SmallVector<Value> ubs =
      getValueOrCreateConstantIndexOp(rewriter, loc, forallOp.getMixedUpperBound());
  SmallVector<Value> steps =
      getValueOrCreateConstantIndexOp(rewriter, loc, forallOp.getMixedStep());

  // Create empty scf.parallel op.
  auto parallelOp = rewriter.create<scf::ParallelOp>(loc, lbs, ubs, steps);
  rewriter.eraseBlock(&parallelOp.getRegion().front());
  rewriter.inlineRegionBefore(forallOp.getRegion(), parallelOp.getRegion(),
                              parallelOp.getRegion().begin());
  // Replace the terminator.
  rewriter.setInsertionPointToEnd(&parallelOp.getRegion().front());
  rewriter.replaceOpWithNewOp<scf::ReduceOp>(parallelOp.getRegion().front().getTerminator());

  // Erase the scf.forall op.
  rewriter.replaceOp(forallOp, parallelOp);
  return success();
}

class LoweringScfForAllToParallelPass final
    : public impl::LoweringScfForAllToParallelBase<LoweringScfForAllToParallelPass> {
  void runOnOperation() override {
    RewritePatternSet patterns(&getContext());
    patterns.add<ForallLowering>(patterns.getContext());
    ConversionTarget target(getContext());
    target.addIllegalOp<scf::ForallOp>();
    target.markUnknownOpDynamicallyLegal([](Operation*) { return true; });
    if (failed(applyPartialConversion(getOperation(), target, std::move(patterns)))) {
      signalPassFailure();
    }
  }
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createLoweringScfForAllToParallelPass() {
  return std::make_unique<LoweringScfForAllToParallelPass>();
}

}  // namespace mlir::nncv