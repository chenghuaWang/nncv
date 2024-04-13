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
      // if parallel
      if (!forOp->hasAttr("parallel")) return;
      auto forOpCanParallel = forOp->getAttr("parallel").cast<mlir::BoolAttr>();
      if (!forOpCanParallel.getValue()) return;

      // replace scf.for to scf.parallel
      auto _inits = forOp.getInitArgs();
      auto _lowerBound = forOp.getLowerBound();
      auto _upperBound = forOp.getUpperBound();
      auto _step = forOp.getStep();

      // insertion point
      mlir::OpBuilder::InsertionGuard guard(rewriter);
      rewriter.setInsertionPointAfter(forOp);  // insert after ggop

      // build parallel op
      auto parallelOp = rewriter.create<mlir::scf::ParallelOp>(
          forOp->getLoc(), /*lower*/ _lowerBound, /*upper*/ _upperBound,
          /*step*/ _step,
          /*inits*/ _inits, /*body*/ nullptr);

      // set body
      mlir::IRMapping for2pfor;
      for2pfor.map(forOp.getInductionVar(), parallelOp.getInductionVars()[0]);
      for (size_t i = 0; i < _inits.size(); ++i) {
        for2pfor.map(_inits[i], parallelOp.getInitVals()[i]);
      }
      rewriter.setInsertionPointToStart(parallelOp.getBody());
      for (auto& op : forOp.getBody()->without_terminator()) { rewriter.clone(op, for2pfor); }

      // replace
      // rewriter.replaceOp(forOp, parallelOp);
    });
  }
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>>
createAdvancedPeeledDispatchedToParallelPass() {
  return std::make_unique<PeeledDispatchedToParallelPass>();
}

}  // namespace mlir::nncv