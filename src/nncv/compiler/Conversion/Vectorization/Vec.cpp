#include "nncv/compiler/Conversion/Vectorization/Vec.hpp"
#include "mlir/Dialect/Linalg/TransformOps/LinalgTransformOps.h"
#include "mlir/Dialect/Linalg/Transforms/Hoisting.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/Transform/LoopExtension/LoopExtensionOps.h"
#include "mlir/Dialect/Vector/Transforms/LoweringPatterns.h"
#include "mlir/Dialect/Vector/Transforms/VectorRewritePatterns.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/Visitors.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/LoopInvariantCodeMotionUtils.h"
#include "mlir/Transforms/Passes.h"
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

std::pair<llvm::SmallVector<int64_t>, llvm::SmallVector<bool>> buildVectorizationSize(
    mlir::Operation* op) {
  if (mlir::isa<mlir::linalg::MatmulOp>(op)) {
    auto _vecSize = ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulVecCpu.vecSize;
    llvm::SmallVector<int64_t> vecSize;
    for (auto item : _vecSize) vecSize.emplace_back(item);
    llvm::SmallVector<bool> scaleDims(vecSize.size(), false);
    return std::make_pair(vecSize, scaleDims);
  }
  if (mlir::isa<mlir::linalg::GenericOp>(op)) {
    auto genericOp = mlir::cast<mlir::linalg::GenericOp>(op);
    // TODO make code below gorgeous
    if (/*default is 3*/ genericOp.getNumParallelLoops() == 3) {
      auto _vecSize =
          ::nncv::compiler::utils::PlatformCtx::getInstance().LinalgGenericVecCpu.vecSize;
      llvm::SmallVector<int64_t> vecSize;
      for (auto item : _vecSize) vecSize.emplace_back(item);
      llvm::SmallVector<bool> scaleDims(vecSize.size(), false);
      return std::make_pair(vecSize, scaleDims);
    } else if (genericOp.getNumParallelLoops() == 2) {
      std::vector<int64_t> _vecSize = {1, 4};
      llvm::SmallVector<int64_t> vecSize;
      for (auto item : _vecSize) vecSize.emplace_back(item);
      llvm::SmallVector<bool> scaleDims(vecSize.size(), false);
      return std::make_pair(vecSize, scaleDims);
    } else if (genericOp.getNumParallelLoops() == 1) {
      std::vector<int64_t> _vecSize = {4};
      llvm::SmallVector<int64_t> vecSize;
      for (auto item : _vecSize) vecSize.emplace_back(item);
      llvm::SmallVector<bool> scaleDims(vecSize.size(), false);
      return std::make_pair(vecSize, scaleDims);
    }
  }
  if (mlir::isa<mlir::linalg::PoolingNhwcMaxOp, mlir::linalg::PoolingNhwcMinOp,
                mlir::linalg::PoolingNhwcSumOp, mlir::linalg::PoolingNhwcMaxUnsignedOp,
                mlir::linalg::PoolingNhwcMinUnsignedOp, mlir::linalg::PoolingNchwMaxOp,
                mlir::linalg::PoolingNchwSumOp>(op)) {
    std::vector<int64_t> _vecSize = {1, 3, 2, 2};
    llvm::SmallVector<int64_t> vecSize;
    for (auto item : _vecSize) vecSize.emplace_back(item);
    llvm::SmallVector<bool> scaleDims(vecSize.size(), false);
    return std::make_pair(vecSize, scaleDims);
  }
  llvm::SmallVector<int64_t> vecRes;
  llvm::SmallVector<bool> scaleRes;
  return std::make_pair(vecRes, scaleRes);
}

mlir::vector::UnrollVectorOptions buildUnrollVectorOptions() {
  mlir::vector::UnrollVectorOptions res;
  res.setFilterConstraint([](mlir::Operation* op) -> mlir::LogicalResult {
    if (mlir::isa<mlir::vector::ContractionOp>(op) || mlir::isa<mlir::vector::TransposeOp>(op))
      return mlir::failure();

    return mlir::success();
  });
  res.setNativeShapeFn([](mlir::Operation* op) -> std::optional<llvm::SmallVector<int64_t>> {
    auto opT = op->getOperandTypes()[0];

    if (!opT.isa<mlir::VectorType>()) return std::nullopt;
    auto vectorT = opT.cast<mlir::VectorType>();
    size_t vectorShapeLen = vectorT.getShape().size();

    if (vectorShapeLen == 0) return std::nullopt;

    llvm::SmallVector<int64_t> _nativeShape;
    for (size_t i = 0; i < vectorShapeLen - 1; ++i) _nativeShape.emplace_back(1);

    // TODO change this.
    _nativeShape.emplace_back(4);

    return _nativeShape;
  });
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
    IRRewriter rewriter(&getContext());
    if (m_enableNvGPU) /*NV Tensor Core 16x16*/ {
      //===----------------------------------------------------------------------===//
      // 1 vectorize all matmul
      //===----------------------------------------------------------------------===//
      {
        llvm::SmallVector<mlir::Operation*> candidates;
        getOperation()->walk([&](linalg::MatmulOp op) {
          // This pass should work on tensor.
          if (op.hasBufferSemantics()) return WalkResult::skip();
          candidates.push_back(op);
          return WalkResult::advance();
        });

        for (mlir::Operation* op : candidates) {
          if (auto linalgOp = mlir::dyn_cast<linalg::LinalgOp>(op)) {
            llvm::SmallVector<int64_t> VectorSizes(3, 16);
            llvm::SmallVector<bool> ScalableVecDims(3, false);
            if (failed(linalg::vectorize(rewriter, op, VectorSizes, ScalableVecDims))) {
              printf("[ Warn ] %s Op can't be vectorized\n",
                     op->getName().getStringRef().str().c_str());
            }
          }
        }
      }

      //===----------------------------------------------------------------------===//
      // 2 Canonicalize mask related ops before lower them
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet maskCanonPatterns(&getContext());
        vector::CreateMaskOp::getCanonicalizationPatterns(maskCanonPatterns, &getContext());
        vector::ConstantMaskOp::getCanonicalizationPatterns(maskCanonPatterns, &getContext());
        vector::MaskOp::getCanonicalizationPatterns(maskCanonPatterns, &getContext());
        if (failed(
                mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(maskCanonPatterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 3 Reduction to Contract
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::vector::populateVectorMaskLoweringPatternsForSideEffectingOps(patterns);
        mlir::vector::populateVectorTransferPermutationMapLoweringPatterns(patterns);
        mlir::vector::populateVectorReductionToContractPatterns(patterns);
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 4 Clean up IR before lowering
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::vector::ContractionOp::getCanonicalizationPatterns(patterns, &getContext());
        mlir::vector::TransposeOp::getCanonicalizationPatterns(patterns, &getContext());
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 5 Lower vector.multi_dimension early
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        llvm::SmallVector<Operation*> ReductionOps;
        getOperation()->walk([&](mlir::vector::MultiDimReductionOp reductionOp) {
          if (llvm::any_of(reductionOp->getOperands(), [](Value operand) {
                return operand.getDefiningOp<vector::TransposeOp>();
              })) {
            ReductionOps.push_back(reductionOp);
          }
          return WalkResult::advance();
        });
        mlir::vector::populateVectorMultiReductionLoweringPatterns(
            patterns, vector::VectorMultiReductionLowering::InnerParallel);
        mlir::FrozenRewritePatternSet frozenSet(std::move(patterns));
        auto ApplyConfig = mlir::GreedyRewriteConfig();
        ApplyConfig.strictMode = mlir::GreedyRewriteStrictness::ExistingOps;
        (void)mlir::applyOpPatternsAndFold(ReductionOps, frozenSet,
                                           /*config=*/ApplyConfig);
      }
    } else /*X86 AVX2 4/8 float32 is supported*/ {
      // return;
      //===----------------------------------------------------------------------===//
      // 1.1 vectorize all linalg generic ops.
      //===----------------------------------------------------------------------===//
      {
        llvm::SmallVector<mlir::Operation*> Candidates;
        getOperation()->walk([&](linalg::LinalgOp op) {
          // This pass should work on tensor.
          if (op.hasBufferSemantics()) return WalkResult::skip();
          if (mlir::isa<linalg::LinalgOp>(op)
              && !mlir::isa<mlir::linalg::PoolingNhwcMaxOp, mlir::linalg::PoolingNhwcMinOp,
                            mlir::linalg::PoolingNhwcSumOp, mlir::linalg::PoolingNhwcMaxUnsignedOp,
                            mlir::linalg::PoolingNhwcMinUnsignedOp, mlir::linalg::PoolingNchwMaxOp,
                            mlir::linalg::PoolingNchwSumOp, mlir::linalg::Conv2DNhwcHwcfOp,
                            mlir::linalg::Conv2DNchwFchwOp, mlir::linalg::Conv2DNhwcFhwcOp,
                            mlir::linalg::Conv1DNcwFcwOp, mlir::linalg::Conv1DNwcWcfOp,
                            mlir::linalg::PoolingNcwMaxOp, mlir::linalg::PoolingNcwSumOp>(op))
            Candidates.push_back(op);
          // TODO Add tensor.pad
          return WalkResult::advance();
        });

        // process Candidates
        for (mlir::Operation* op : Candidates) {
          if (auto linalgOp = mlir::dyn_cast<linalg::LinalgOp>(op)) {
            auto [VectorSizes, ScalableVecDims] = buildVectorizationSize(op);
            if (failed(linalg::vectorize(rewriter, op, VectorSizes, ScalableVecDims))) {
              printf("[ Warn ] %s Op can't be vectorized\n",
                     op->getName().getStringRef().str().c_str());
            }
          } else if (auto padOp = dyn_cast<tensor::PadOp>(op)) {
          }
        }
      }

      //===----------------------------------------------------------------------===//
      // 1.2 vectorize all linalg.conv and linalg.pad
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::linalg::populateConvolutionVectorizationPatterns(patterns);
        mlir::linalg::populatePadOpVectorizationPatterns(patterns);
        mlir::linalg::ControlDropUnitDims option;
        option.rankReductionStrategy =
            mlir::linalg::ControlDropUnitDims::RankReductionStrategy::ReassociativeReshape;
        mlir::linalg::populateFoldUnitExtentDimsPatterns(patterns, option);
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 1.3 Canonicalize mask related ops before lower them
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet maskCanonPatterns(&getContext());
        vector::CreateMaskOp::getCanonicalizationPatterns(maskCanonPatterns, &getContext());
        vector::ConstantMaskOp::getCanonicalizationPatterns(maskCanonPatterns, &getContext());
        vector::MaskOp::getCanonicalizationPatterns(maskCanonPatterns, &getContext());
        if (failed(
                mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(maskCanonPatterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 1.4 Reduction to Contract
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::vector::populateVectorMaskLoweringPatternsForSideEffectingOps(patterns);
        mlir::vector::populateVectorTransferPermutationMapLoweringPatterns(patterns);
        mlir::vector::populateVectorReductionToContractPatterns(patterns);
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 1.5 Clean up IR before lowering
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::vector::ContractionOp::getCanonicalizationPatterns(patterns, &getContext());
        mlir::vector::TransposeOp::getCanonicalizationPatterns(patterns, &getContext());
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 1.6 Lower vector.multi_dimension early
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        llvm::SmallVector<Operation*> ReductionOps;
        getOperation()->walk([&](mlir::vector::MultiDimReductionOp reductionOp) {
          if (llvm::any_of(reductionOp->getOperands(), [](Value operand) {
                return operand.getDefiningOp<vector::TransposeOp>();
              })) {
            ReductionOps.push_back(reductionOp);
          }
          return WalkResult::advance();
        });
        mlir::vector::populateVectorMultiReductionLoweringPatterns(
            patterns, vector::VectorMultiReductionLowering::InnerParallel);
        mlir::FrozenRewritePatternSet frozenSet(std::move(patterns));
        auto ApplyConfig = mlir::GreedyRewriteConfig();
        ApplyConfig.strictMode = mlir::GreedyRewriteStrictness::ExistingOps;
        (void)mlir::applyOpPatternsAndFold(ReductionOps, frozenSet,
                                           /*config=*/ApplyConfig);
      }

      //===----------------------------------------------------------------------===//
      // 2.0 Unroll
      //===----------------------------------------------------------------------===//
      // unroll vector<4x4> or others but without contraction op in vector.
      // {
      //   mlir::RewritePatternSet patterns(&getContext());
      //   mlir::vector::populateVectorUnrollPatterns(patterns, buildUnrollVectorOptions());
      //   if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      //     signalPassFailure();
      //   }
      // }
      {
        mlir::RewritePatternSet patterns(&getContext());
        auto options = mlir::vector::VectorTransformsOptions().setVectorTransformsOptions(
            mlir::vector::VectorContractLowering::OuterProduct);
        mlir::vector::populateVectorContractLoweringPatterns(patterns, options);
        mlir::vector::TransposeOp::getCanonicalizationPatterns(patterns, &getContext());
        if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 3.1 Clear High dimension vector
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::vector::populateCastAwayVectorLeadingOneDimPatterns(patterns);
        mlir::vector::TransferReadOp::getCanonicalizationPatterns(patterns, &getContext());
        mlir::vector::TransferWriteOp::getCanonicalizationPatterns(patterns, &getContext());
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 3.2 Clear High dimension vector
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::vector::populateVectorInsertExtractStridedSliceDecompositionPatterns(patterns);
        mlir::vector::ExtractOp::getCanonicalizationPatterns(patterns, &getContext());
        if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 4 Hoisting
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        // transform dialect.
        linalg::hoistRedundantVectorTransfers(getOperation());
        getOperation()->walk([&](LoopLikeOpInterface loopLike) {
          (void)mlir::hoistLoopInvariantSubsets(rewriter, loopLike);
        });
      }
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::vector::ExtractStridedSliceOp::getCanonicalizationPatterns(patterns, &getContext());
        mlir::vector::populateVectorTransferPermutationMapLoweringPatterns(patterns);
        if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 5 lower reduction-unrolled
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        auto options = mlir::vector::VectorTransformsOptions().setVectorTransformsOptions(
            mlir::vector::VectorContractLowering::ParallelArith);
        mlir::vector::populateVectorContractLoweringPatterns(patterns, options);
        mlir::vector::TransposeOp::getCanonicalizationPatterns(patterns, &getContext());
        if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 6 lower vector broadcast/transpose and contraction
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        auto options =
            mlir::vector::VectorTransformsOptions()
                .setVectorTransformsOptions(mlir::vector::VectorContractLowering::OuterProduct)
                .setVectorTransposeLowering(mlir::vector::VectorTransposeLowering::EltWise);
        mlir::vector::populateVectorBroadcastLoweringPatterns(patterns);
        mlir::vector::populateVectorContractLoweringPatterns(patterns, options);
        mlir::vector::populateVectorMultiReductionLoweringPatterns(
            patterns, vector::VectorMultiReductionLowering::InnerParallel);
        mlir::vector::populateVectorTransposeLoweringPatterns(patterns, options);
        if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // 7 Clean up all
      //===----------------------------------------------------------------------===//
      {
        mlir::RewritePatternSet patterns(&getContext());
        mlir::vector::populateCastAwayVectorLeadingOneDimPatterns(patterns);
        mlir::vector::InsertOp::getCanonicalizationPatterns(patterns, &getContext());
        mlir::vector::ExtractOp::getCanonicalizationPatterns(patterns, &getContext());
        mlir::vector::TransferReadOp::getCanonicalizationPatterns(patterns, &getContext());
        mlir::vector::TransferWriteOp::getCanonicalizationPatterns(patterns, &getContext());
        mlir::vector::ReductionOp::getCanonicalizationPatterns(patterns, &getContext());
        if (failed(applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          return signalPassFailure();
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