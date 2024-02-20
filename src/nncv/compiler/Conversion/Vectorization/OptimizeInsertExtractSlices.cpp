#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/Transforms/Hoisting.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Dialect/Vector/Transforms/VectorTransforms.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/LoopInvariantCodeMotionUtils.h"

#include "nncv/compiler/Conversion/Passes.h"
#include "nncv/compiler/Conversion/Vectorization/OptimizeInsertExtractSlices.hpp"

#define GEN_PASS_DEF_OPTIMIZETENSORINSERTEXTRACTSLICES
#include "Conversion/Passes.h.inc"

namespace mlir {
namespace nncv {

namespace {
class OptimizeTensorInsertExtractSlicesPass
    : public ::impl::OptimizeTensorInsertExtractSlicesBase<OptimizeTensorInsertExtractSlicesPass> {
 public:
  using OptimizeTensorInsertExtractSlicesBase::OptimizeTensorInsertExtractSlicesBase;

  void getDependentDialects(DialectRegistry& registry) const override {
    registry.insert<scf::SCFDialect, vector::VectorDialect>();
  }
  void runOnOperation() override;
};

void OptimizeTensorInsertExtractSlicesPass::runOnOperation() {
  auto funcOp = getOperation();
  linalg::hoistRedundantVectorTransfers(cast<func::FuncOp>(funcOp));
  IRRewriter rewriter(funcOp->getContext());
  // TODO: walking in some reverse / inside-out order would be more efficient
  // and would capture more cases.
  funcOp.walk([&](scf::ForOp forOp) { hoistLoopInvariantSubsets(rewriter, forOp); });
  vector::transferOpflowOpt(rewriter, funcOp);
  MLIRContext* context = &getContext();

  RewritePatternSet patterns(context);
  populateVectorTransferTensorSliceTransforms(patterns);
  if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(patterns)))) {
    return signalPassFailure();
  }
}

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>>
createOptimizeTensorInsertExtractSlicesPass() {}
}  // namespace nncv
}  // namespace mlir