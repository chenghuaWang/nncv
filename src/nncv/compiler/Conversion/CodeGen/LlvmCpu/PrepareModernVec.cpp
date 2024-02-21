#include "mlir/Dialect/Linalg/IR/LinalgInterfaces.h"
#include "mlir/Dialect/Tensor/Transforms/Transforms.h"
#include "mlir/IR/PatternMatch.h"
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
#define GEN_PASS_DEF_PREPAREMODERNVEC
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

bool vectorizeMatMul(IRRewriter& rewriter, mlir::Operation* op) {
  llvm::SmallVector<int64_t> VectorSizes(3, 4);
  llvm::SmallVector<bool> ScalableVecDims(3, false);  // only for scable vec
  if (failed(linalg::vectorize(rewriter, op, VectorSizes, ScalableVecDims))) { return false; }
  return true;
}

bool vectorizeGeneric(IRRewriter& rewriter, mlir::Operation* op) {
  // TODO
  return true;
}

void emitErrorWhenFailed(bool isOk, mlir::Operation* op) {
  if (!isOk) {
    printf("[ Warn ] When tiling %s op, failed.\n", op->getName().getStringRef().str().c_str());
  }
}

class PrepareModernVecPass final : public impl::PrepareModernVecBase<PrepareModernVecPass> {
  void runOnOperation() override {
    // Vectorization all
    IRRewriter rewriter(&getContext());
    SmallVector<mlir::Operation*> matMulCandidates;
    SmallVector<mlir::Operation*> genericCandidates;
    getOperation().walk([&](mlir::linalg::LinalgOp op) {
      if (mlir::isa<mlir::linalg::MatmulOp>(op)) {
        matMulCandidates.push_back(op);
        return;
      }
      if (mlir::isa<mlir::linalg::GenericOp>(op)) {
        genericCandidates.push_back(op);
        return;
      }
    });

    for (auto op : matMulCandidates) { emitErrorWhenFailed(vectorizeMatMul(rewriter, op), op); }
    for (auto op : genericCandidates) { emitErrorWhenFailed(vectorizeGeneric(rewriter, op), op); }

    // populate Conv vec.
    // clang-format off
    // %tiled = transform.structured.decompose %tiled_conv2 : (!transform.any_op) -> !transform.any_op
    // clang-format on
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::populateConvolutionVectorizationPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    // clean up
    // if using transform dialect:
    // clang-format off
    // transform.apply_patterns to %func03 {
    //   transform.apply_patterns.canonicalization
    //   transform.apply_patterns.tensor.fold_tensor_subset_ops_into_vector_transfers
    //   transform.apply_patterns.vector.lower_masked_transfers
    //   transform.apply_patterns.vector.transfer_permutation_patterns
    //   transform.apply_patterns.vector.reduction_to_contract
    //   transform.apply_patterns.canonicalization
    //   transform.apply_patterns.linalg.tiling_canonicalization
    // } : !transform.any_op
    // transform.apply_cse to %func03 : !transform.any_op
    // transform.structured.hoist_redundant_vector_transfers %func03 : (!transform.any_op) -> !transform.any_op
    // clang-format on
    {
      mlir::RewritePatternSet patterns(&getContext());
      // transform.apply_patterns.tensor.fold_tensor_subset_ops_into_vector_transfers
      mlir::tensor::populateFoldTensorSubsetIntoVectorTransferPatterns(patterns);

      // transform.apply_patterns.vector.lower_masked_transfers
      mlir::vector::populateVectorMaskLoweringPatternsForSideEffectingOps(patterns);

      // transform.apply_patterns.vector.transfer_permutation_patterns
      mlir::vector::populateVectorTransferPermutationMapLoweringPatterns(patterns);

      // transform.apply_patterns.vector.reduction_to_contract
      mlir::vector::populateVectorReductionToContractPatterns(patterns);

      // transform.apply_patterns.linalg.tiling_canonicalization
      mlir::linalg::populateLinalgTilingCanonicalizationPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }
  }
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createPrepareModernVecPass() {
  return std::make_unique<PrepareModernVecPass>();
}

}  // namespace mlir::nncv