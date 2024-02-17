#include "nncv/compiler/Conversion/LinalgOptimize/DecomposeTransGen.hpp"

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
#include "mlir/Dialect/Tensor/Transforms/Transforms.h"
#include "mlir/Dialect/Transform/IR/TransformInterfaces.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "nncv/compiler/TransformCommon/Common.hpp"
#include "mlir/Dialect/Linalg/TransformOps/DialectExtension.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_DECOMPOSETRANSFORMGEN
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class DecomposeTransformGenPass
    : public impl::DecomposeTransformGenBase<DecomposeTransformGenPass> {
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                    mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect,
                    mlir::transform::TransformDialect>();
    mlir::linalg::registerTransformDialectExtension(registry);
  }

  void runOnOperation() override {
    bool ifFuncHasLinalgOp = false;
    getOperation().walk([&](mlir::linalg::LinalgOp op) { ifFuncHasLinalgOp = true; });

    if (ifFuncHasLinalgOp) {
      // create module transform
      auto transOp =
          nncv::createTransformRegion(getOperation(), nncv::createTransformDecomposeLinalg);

      auto res = mlir::transform::applyTransforms(
          getOperation(), transOp, {}, mlir::transform::TransformOptions(), /*enforce top*/ false);

      if (res.failed()) signalPassFailure();

      // Clean All IR
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::tensor::populateMergeConsecutiveInsertExtractSlicePatterns(patterns);
        tensor::InsertSliceOp::getCanonicalizationPatterns(patterns, &getContext());
        tensor::ExtractSliceOp::getCanonicalizationPatterns(patterns, &getContext());
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }
    }
  }
};

}  // namespace

std::unique_ptr<mlir::Pass> createDecomposeTransformGenPass() {
  return std::make_unique<DecomposeTransformGenPass>();
}

}  // namespace mlir::nncv