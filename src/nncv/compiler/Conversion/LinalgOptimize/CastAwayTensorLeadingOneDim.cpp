#include "nncv/compiler/Conversion/LinalgOptimize/CastAwayTensorLeadingOneDim.hpp"

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
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_LINALGOPCASTAWAYTENSORLEADINGONEDIM
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
namespace {

class LinalgOpCastAwayTensorLeadingOneDimPass
    : public impl::LinalgOpCastAwayTensorLeadingOneDimBase<
          LinalgOpCastAwayTensorLeadingOneDimPass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::ControlDropUnitDims option;
      option.rankReductionStrategy =
          mlir::linalg::ControlDropUnitDims::RankReductionStrategy::ReassociativeReshape;
      mlir::linalg::populateFoldUnitExtentDimsPatterns(patterns, option);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createLinalgOpCastAwayTensorLeadingOneDimPass() {
  return std::make_unique<LinalgOpCastAwayTensorLeadingOneDimPass>();
}

}  // namespace nncv
}  // namespace mlir