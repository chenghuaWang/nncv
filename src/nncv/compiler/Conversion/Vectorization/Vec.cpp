#include "nncv/compiler/Conversion/Vectorization/Vec.hpp"
#include "mlir/Dialect/Linalg/TransformOps/LinalgTransformOps.h"
#include "mlir/Dialect/Linalg/Transforms/Hoisting.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/Transform/LoopExtension/LoopExtensionOps.h"
#include "mlir/Dialect/Vector/Transforms/LoweringPatterns.h"
#include "mlir/Dialect/Vector/Transforms/VectorRewritePatterns.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/LoopInvariantCodeMotionUtils.h"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"
#include "mlir/Transforms/DialectConversion.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_VECTORIZATION
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {

// using info from plateform ctx.
vector::UnrollVectorOptions buildUnrollVectorOptions() {
  vector::UnrollVectorOptions res;
  // TODO use set native shape func
  // Ref:
  // https://github.com/openxla/iree/blob/28de72c482898a358bcce333c3fc91663cae267f/compiler/src/iree/compiler/Codegen/LLVMGPU/LLVMGPUTensorCoreVectorization.cpp#L65
  res.setNativeShape({1, 1, 4});

  return res;
}

vector::VectorTransformsOptions buildVectorTransformsOptions() {
  vector::VectorTransformsOptions res;
  res.setVectorTransformsOptions(vector::VectorContractLowering::OuterProduct);
  return res;
}

namespace {

class VectorizationPass : public impl::VectorizationBase<VectorizationPass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    mlir::RewritePatternSet patterns(&getContext());
    IRRewriter rewriter(&getContext());
    if (m_enableNvGPU) {
    } else {
      // Stage 1.1 vectorize all linalg.conv and linalg.pad
      {
        mlir::linalg::populateConvolutionVectorizationPatterns(patterns);
        mlir::linalg::populatePadOpVectorizationPatterns(patterns);
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      // Stage 1.2 vectorize all linalg generic ops.
      {
        patterns.clear();
        getOperation()->walk([&](linalg::LinalgOp op) {
          // This pass should work on tensor.
          if (op.hasBufferSemantics()) return signalPassFailure();
          OpBuilder::InsertionGuard guard(rewriter);
          rewriter.setInsertionPoint(op);

          // transform dialect
          if (failed(linalg::vectorize(rewriter, op))) return;
        });
      }

      // Stage 1.3 vectorize all
      {
        patterns.clear();
        mlir::vector::populateVectorReductionToContractPatterns(patterns);
        mlir::vector::populateVectorTransferLoweringPatterns(patterns);
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      return;

      // Stage 2. Unroll
      {
        patterns.clear();
        mlir::vector::populateVectorUnrollPatterns(patterns, buildUnrollVectorOptions());
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      // Stage 3. Clear High dimension vector
      {
        patterns.clear();
        mlir::vector::populateCastAwayVectorLeadingOneDimPatterns(patterns);
        mlir::vector::populateVectorInsertExtractStridedSliceDecompositionPatterns(patterns);
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      // Stage 4. Hoisting
      {
        patterns.clear();
        // transform dialect.
        getOperation()->walk([&](func::FuncOp op) {});
      }

      return;

      // Stage 5. lowering vector, but not to llvm.
      {
        patterns.clear();
        mlir::vector::populateVectorContractLoweringPatterns(patterns,
                                                             buildVectorTransformsOptions());
        // mlir::vector::populateVectorMaskLoweringPatternsForSideEffectingOps(patterns);
        // mlir::vector::populateVectorBroadcastLoweringPatterns(patterns);
        // mlir::vector::populateVectorShapeCastLoweringPatterns(patterns);
        // mlir::vector::populateVectorOuterProductLoweringPatterns(patterns);
        // mlir::vector::populateVectorMaskOpLoweringPatterns(patterns);
        // mlir::vector::populateVectorGatherLoweringPatterns(patterns);
        // mlir::vector::populateVectorTransferPermutationMapLoweringPatterns(patterns);
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }
    }
  }

  void setNvGPU(bool flag = true) { m_enableNvGPU = flag; }
  bool isNvGPUEnable() { return m_enableNvGPU; }

 private:
  bool m_enableNvGPU = false;
};

}  // namespace

std::unique_ptr<mlir::Pass> createVectorizationPass(bool flag) {
  auto res = std::make_unique<VectorizationPass>();
  res->setNvGPU(flag);
  return res;
}
}  // namespace nncv
}  // namespace mlir