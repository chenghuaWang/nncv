#include "nncv/compiler/Conversion/CodeGen/Advance/PeeledDispatchedToParallel.hpp"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlowOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/Passes.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_ADVANCEDPEELEDDISPATCHEDTOPARALLEL
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class PeeledDispatchedToParallelPass final
    : public impl::AdvancedPeeledDispatchedToParallelBase<PeeledDispatchedToParallelPass> {
  void runOnOperation() override {
    IRRewriter rewriter(&getContext());
    auto topFuncOp = getOperation();
    topFuncOp.walk([&](mlir::scf::ForOp forOp) {
      // just process the top level scf.for loop for cpu target.
      if (!mlir::isa<mlir::func::FuncOp>(forOp->getParentOp())) return;

      // replace scf.for to scf.parallel
      auto _inits = forOp.getInits();
      auto _lowerBound = forOp.getLowerBound();
      auto _upperBound = forOp.getUpperBound();
      auto _step = forOp.getStep();

      // build parallel op
      auto parallelOp = rewriter.create<mlir::scf::ParallelOp>(
          forOp->getLoc(), /*lower*/ _lowerBound, /*upper*/ _upperBound, /*step*/ _step,
          /*inits*/ _inits, /*body*/ nullptr);

      // set body
      rewriter.inlineRegionBefore(forOp.getBodyRegion(), parallelOp.getBodyRegion(),
                                  parallelOp.getBodyRegion().end());

      // replace
      rewriter.replaceOp(forOp, parallelOp);
    });
  }
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>>
createAdvancedPeeledDispatchedToParallelPass() {
  return std::make_unique<PeeledDispatchedToParallelPass>();
}

}  // namespace mlir::nncv