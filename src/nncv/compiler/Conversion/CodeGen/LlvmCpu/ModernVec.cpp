#include "nncv/compiler/Conversion/CodeGen/LlvmCpu/ModernVec.hpp"
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
#include "nncv/compiler/Conversion/Vectorization/VectorizePad.hpp"
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

#include "llvm/ADT/TypeSwitch.h"
#include "nncv/compiler/Conversion/Passes.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_MODERNVEC
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

class ModernVectorizationAllPass final : public impl::ModernVecBase<ModernVectorizationAllPass> {
  void runOnOperation() override {
    // clean up ir first
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::vector::populateCastAwayVectorLeadingOneDimPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.lower_contraction lowering_strategy = "outerproduct"
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::vector::VectorTransformsOptions options;
      options.setVectorTransformsOptions(mlir::vector::VectorContractLowering::OuterProduct);
      mlir::vector::populateVectorContractLoweringPatterns(patterns, options);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.transfer_permutation_patterns
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::vector::populateVectorTransferPermutationMapLoweringPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.lower_multi_reduction lowering_strategy = "innerparallel"
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::vector::populateVectorMultiReductionLoweringPatterns(
          patterns, mlir::vector::VectorMultiReductionLowering::InnerReduction);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.split_transfer_full_partial split_transfer_strategy =
    //   "linalg-copy"
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      vector::VectorTransformsOptions vectorTransformOptions;
      vectorTransformOptions.setVectorTransferSplit(mlir::vector::VectorTransferSplit::LinalgCopy);
      mlir::vector::populateVectorTransferFullPartialPatterns(patterns, vectorTransformOptions);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.transfer_to_scf max_transfer_rank = 1 full_unroll = true
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      VectorTransferToSCFOptions vectorTransferToSCFOptions =
          VectorTransferToSCFOptions().enableFullUnroll(true).setTargetRank(1);
      mlir::populateVectorToSCFConversionPatterns(patterns, vectorTransferToSCFOptions);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.lower_transfer max_transfer_rank = 1
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::vector::populateVectorTransferLoweringPatterns(patterns, 1);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.lower_shape_cast
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::vector::populateVectorShapeCastLoweringPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }
    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.lower_transpose lowering_strategy = "shuffle_1d"
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      vector::VectorTransformsOptions vectorTransformOptions;
      vectorTransformOptions.setVectorTransposeLowering(
          mlir::vector::VectorTransposeLowering::Shuffle1D);
      mlir::vector::populateVectorTransposeLoweringPatterns(patterns, vectorTransformOptions);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // transform.apply_patterns to %f {
    //   transform.apply_patterns.vector.lower_outerproduct
    // } : !transform.any_op
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::vector::populateVectorOuterProductLoweringPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }
  }
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createModernVectorizationAllPass() {
  return std::make_unique<ModernVectorizationAllPass>();
}

}  // namespace mlir::nncv