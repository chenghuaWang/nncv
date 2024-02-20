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
#define GEN_PASS_DEF_VECTORIZATION
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {

// this func is ref from IREE
int getComputeVectorSize(int64_t size) {
  for (int i : {8, 4, 3, 2}) {
    if (size % i == 0) return i;
  }
  return 1;
}

// this func is ref from IREE
int getMemoryVectorSize(Value source, Type scalarType, int64_t size) {
  int bitwidth = scalarType.getIntOrFloatBitWidth();
  while (auto sliceOp = source.getDefiningOp<tensor::ExtractSliceOp>())
    source = sliceOp.getSource();
  if (!matchPattern(source, m_Constant())) {
    // If we are not reading from a constant array that is embedded in the
    // kernel, try to use a large vector size matching the bitwidth to read in
    // 128-bit chunks. This helps with memory access performance. Such vector
    // sizes are not native in SPIR-V though; this relies on following passes to
    // bitcast them to 32-bit 4-element vectors to be valid.
    if (bitwidth <= 8 && size % 16 == 0) return 16;
    if (bitwidth <= 16 && size % 8 == 0) return 8;
  }
  if (bitwidth <= 32 && size % 4 == 0) return 4;
  return size % 2 == 0 ? 2 : 1;
}

// this func is ref from IREE
SmallVector<int64_t> getNativeVectorShapeImpl(VectorTransferOpInterface op) {
  auto vecType = op.getVectorType();
  SmallVector<int64_t> nativeSize(vecType.getRank(), 1);
  for (const auto& [index, dim] : llvm::enumerate(op.getPermutationMap().getResults())) {
    if (auto dimExpr = dyn_cast<AffineDimExpr>(dim)) {
      if (dimExpr.getPosition() == op.getPermutationMap().getNumDims() - 1) {
        nativeSize[index] = getMemoryVectorSize(op.getSource(), vecType.getElementType(),
                                                vecType.getShape()[index]);
      }
    }
  }
  return nativeSize;
}

// this func is ref from IREE
Operation* stripElementBitPatternPreservingParents(Value op) {
  while (Operation* parentOp = op.getDefiningOp()) {
    Value source =
        TypeSwitch<Operation*, Value>(parentOp)
            .Case<vector::BroadcastOp>(
                [](vector::BroadcastOp broadcast) { return broadcast.getVector(); })
            .Case<vector::ExtractOp, vector::ExtractElementOp, vector::ExtractStridedSliceOp>(
                [](auto extract) { return extract.getVector(); })
            .Case<vector::InsertOp, vector::InsertElementOp, vector::InsertStridedSliceOp>(
                [](auto insert) { return insert.getSource(); })
            .Case<vector::TransposeOp>(
                [](vector::TransposeOp transpose) { return transpose.getVector(); })
            .Default([](Operation*) { return nullptr; });

    if (!source) break;
    op = source;
  }

  return op.getDefiningOp();
}

// this func is ref from IREE
/// Returns true when |op| has the i32 element type that is likely to be result
/// of a zero/sign extension from i8.
bool mayExtI8ToI32(Value op) {
  if (!getElementTypeOrSelf(op.getType()).isInteger(32)) return false;

  // Look through vector operations created by vector unrolling patterns,
  // hoping to find a zero/sign extension op. Note that we do not need to find
  // the exact definition for |op| as the final extension will be matched by
  // other patterns -- we only need a good enough proxy to know that one is
  // likely to be found after canonicalization.
  // TODO(#12543): Implement integer narrowing patterns to be able to tell for
  // sure.
  Operation* def = stripElementBitPatternPreservingParents(op);
  Type inTy;

  if (auto ext = dyn_cast_or_null<arith::ExtSIOp>(def)) {
    inTy = getElementTypeOrSelf(ext.getIn().getType());
  } else if (auto ext = dyn_cast_or_null<arith::ExtUIOp>(def)) {
    inTy = getElementTypeOrSelf(ext.getIn().getType());
  } else {
    return false;
  }

  return inTy.isInteger(8);
}

// this func is ref from IREE
/// Succeeds when |contract| is a i32 matmul whose LHS and RHS operands may be
/// result of zero/sign extension of i8 inputs.
LogicalResult detectI8ToI32Matmul(vector::ContractionOp contract) {
  if (contract.getKind() != vector::CombiningKind::ADD) return failure();

  if (!mayExtI8ToI32(contract.getLhs()) || !mayExtI8ToI32(contract.getRhs())) return failure();

  ArrayRef<Attribute> iteratorTypes = contract.getIteratorTypes().getValue();
  if (iteratorTypes.size() != 3) return failure();

  return success(vector::isParallelIterator(iteratorTypes[0])
                 && vector::isParallelIterator(iteratorTypes[1])
                 && vector::isReductionIterator(iteratorTypes[2]));
}

// this func is ref from IREE
/// Returns the index of the reduction dimension.
unsigned getReductionDim(vector::ContractionOp contract) {
  AffineMap resultMap = contract.getIndexingMapsArray().back();
  ArrayRef<Attribute> iteratorTypes = contract.getIteratorTypes().getValue();
  for (auto [idx, it] : llvm::enumerate(iteratorTypes)) {
    if (vector::isReductionIterator(it)) { return idx; }
  }

  // Return the last index as a fallback.
  return resultMap.getNumDims() - 1;
}

// this func is ref from IREE
unsigned getInnermostParallelDim(vector::ContractionOp contract) {
  AffineMap resultMap = contract.getIndexingMapsArray().back();
  return resultMap.getDimPosition(resultMap.getNumResults() - 1);
}

SmallVector<int64_t> getNativeVectorShapeImpl(vector::ContractionOp op,
                                              bool targetSupportsDotProd) {
  // Find the contract dimension to unroll. This depends on whether we use the
  // outer product or inner product lowering. Outer product is the default
  // strategy.
  bool lowerToInnerProd = targetSupportsDotProd && succeeded(detectI8ToI32Matmul(op));
  unsigned unrollDim = lowerToInnerProd ? getReductionDim(op) : getInnermostParallelDim(op);
  auto iteratorTypes = op.getIteratorTypes().getValue();
  SmallVector<int64_t> nativeSize(iteratorTypes.size(), 1);
  SmallVector<int64_t> bounds;
  op.getIterationBounds(bounds);
  nativeSize[unrollDim] = getComputeVectorSize(bounds[unrollDim]);
  return nativeSize;
}

SmallVector<int64_t> getNativeVectorShapeImpl(vector::MultiDimReductionOp op) {
  // Unroll all reduction dimensions by size 1 for vector.multi_reduction.
  VectorType srcVectorType = op.getSourceVectorType();
  auto nativeSize = llvm::to_vector(srcVectorType.getShape());
  auto dims = op.getReductionDims().getAsValueRange<IntegerAttr>();
  for (const auto& dimAttr : dims) { nativeSize[dimAttr.getZExtValue()] = 1; }
  return nativeSize;
}

SmallVector<int64_t> getNativeVectorShapeImpl(vector::ReductionOp op) {
  VectorType srcVectorType = op.getSourceVectorType();
  assert(srcVectorType.getRank() == 1);  // Guaranteed by semantics
  int64_t vectorSize = getComputeVectorSize(srcVectorType.getDimSize(0));
  return {vectorSize};
}

SmallVector<int64_t> getNativeVectorShapeImpl(vector::TransposeOp op) {
  VectorType vectorType = op.getResultVectorType();
  SmallVector<int64_t> nativeSize(vectorType.getRank(), 1);
  nativeSize.back() = getComputeVectorSize(vectorType.getShape().back());
  return nativeSize;
}

SmallVector<int64_t> getNativeVectorShapeImpl(vector::GatherOp op) {
  VectorType vectorType = op.getVectorType();
  SmallVector<int64_t> nativeSize(vectorType.getRank(), 1);
  nativeSize.back() = getComputeVectorSize(vectorType.getShape().back());
  return nativeSize;
}

std::optional<SmallVector<int64_t>> getNativeVectorShape(Operation* op,
                                                         bool targetSupportsDotProd) {
  if (OpTrait::hasElementwiseMappableTraits(op) && op->getNumResults() == 1) {
    if (auto vecType = llvm::dyn_cast<VectorType>(op->getResultTypes()[0])) {
      SmallVector<int64_t> nativeSize(vecType.getRank(), 1);
      nativeSize.back() = getComputeVectorSize(vecType.getShape().back());
      return nativeSize;
    }
  }

  return TypeSwitch<Operation*, std::optional<SmallVector<int64_t>>>(op)
      .Case<VectorTransferOpInterface, vector::MultiDimReductionOp, vector::ReductionOp,
            vector::TransposeOp, vector::GatherOp>(
          [](auto typedOp) { return getNativeVectorShapeImpl(typedOp); })
      .Case<vector::ContractionOp>(
          [=](auto contract) { return getNativeVectorShapeImpl(contract, targetSupportsDotProd); })
      .Default([](Operation*) { return std::nullopt; });
}

/// Adds patterns to unroll vector ops to AVX2 native vector size.
void populateVectorUnrollPatterns(RewritePatternSet& patterns, bool targetSupportsDotProd) {
  auto options = vector::UnrollVectorOptions().setNativeShapeFn(
      [=](auto op) { return getNativeVectorShape(op, targetSupportsDotProd); });
  vector::populateVectorUnrollPatterns(patterns, options);
}

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
      std::vector<int64_t> _vecSize = {1, 8};
      llvm::SmallVector<int64_t> vecSize;
      for (auto item : _vecSize) vecSize.emplace_back(item);
      llvm::SmallVector<bool> scaleDims(vecSize.size(), false);
      return std::make_pair(vecSize, scaleDims);
    } else if (genericOp.getNumParallelLoops() == 1) {
      std::vector<int64_t> _vecSize = {8};
      llvm::SmallVector<int64_t> vecSize;
      for (auto item : _vecSize) vecSize.emplace_back(item);
      llvm::SmallVector<bool> scaleDims(vecSize.size(), false);
      return std::make_pair(vecSize, scaleDims);
    }
  }
  llvm::SmallVector<int64_t> vecRes;
  llvm::SmallVector<bool> scaleRes;
  return std::make_pair(vecRes, scaleRes);
}

// my naive unroll function.
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
      MLIRContext* context = &getContext();
      auto funcOp = getOperation();
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
        // FIXME
        // mlir::linalg::populatePadOpVectorizationPatterns(patterns);
        mlir::linalg::ControlDropUnitDims option;
        option.rankReductionStrategy =
            mlir::linalg::ControlDropUnitDims::RankReductionStrategy::ReassociativeReshape;
        mlir::linalg::populateFoldUnitExtentDimsPatterns(patterns, option);
        if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
          signalPassFailure();
        }
      }

      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------

      //===----------------------------------------------------------------------===//
      // Pad All.
      // First apply vectorization to generate vectors of the original tensor
      // shape for tensor.pad ops.
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet patterns(context);
        populateVectorizePadPatterns(patterns);
        if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // Special peephole optimizations to clean up IR before further processing.
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet patterns(&getContext());
        // Pull in patterns to shuffle broadcast/transpose ops around in order to
        // cancel them or embed into contract ops. Embedding in the flexible
        // contract ops will help to sustain the structure through various
        // transformations.
        vector::populateVectorReductionToContractPatterns(patterns);
        // Pull in patterns to canonicalize transfer ops.
        vector::populateVectorTransferPermutationMapLoweringPatterns(patterns);
        // Fold consumer add ops into the contraction op itself.
        vector::ContractionOp::getCanonicalizationPatterns(patterns, context);
        // Fold transpose ops if possible as we cannot unroll it later.
        vector::TransposeOp::getCanonicalizationPatterns(patterns, context);

        if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // High dimension contraction can appear after vectorizing ops like 1-D
      // convolution. Those 1-D convolution ops typically have a leading unit
      // batch dimension. Try to drop that to map to matmul dimensions better.
      //===----------------------------------------------------------------------===//
      {
        SmallVector<vector::ContractionOp> contractOps;
        funcOp.walk([&](vector::ContractionOp op) {
          if (op.getIteratorTypes().size() > 3) contractOps.push_back(op);
        });
        for (vector::ContractionOp op : contractOps) {
          OpBuilder builder(op);
          IRRewriter rewriter(builder);
          (void)vector::castAwayContractionLeadingOneDim(op, rewriter);
        }
      }

      //===----------------------------------------------------------------------===//
      // Fold tensor.extract_slice/insert_slice ops into transfer ops. This helps
      // to remove those tensor slice ops so that we can enable further vector op
      // transformations.
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet patterns(context);
        vector::TransferReadOp::getCanonicalizationPatterns(patterns, context);
        vector::TransferWriteOp::getCanonicalizationPatterns(patterns, context);
        populateVectorTransferTensorSliceTransforms(patterns);

        if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // Lower vector.multi_dimension early if any operand is a transpose op.
      // The lowering itself generates transpose ops. This helps to cancel
      // transpose ops. vector.multi_reduction is arguably a higher level op and
      // the lowering also unrolls the multi_reduction op, so it makes sense to
      // happen before normal unrolling.
      //===----------------------------------------------------------------------===//
      {
        SmallVector<Operation*> reductionOps;
        funcOp.walk([&](vector::MultiDimReductionOp reductionOp) {
          if (llvm::any_of(reductionOp->getOperands(), [](Value operand) {
                return operand.getDefiningOp<vector::TransposeOp>();
              }))
            reductionOps.push_back(reductionOp);
          return WalkResult::advance();
        });
        RewritePatternSet patterns(context);
        vector::populateVectorMultiReductionLoweringPatterns(
            patterns, vector::VectorMultiReductionLowering::InnerParallel);
        if (failed(applyOpPatternsAndFold(reductionOps, std::move(patterns)))) {
          funcOp.emitOpError("vector lowering failed");
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // Then unroll vectors to native vector size. We try to use 256-bit
      // vectors for memory access and 8/4/2/1 vector sizes for computation.
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet patterns(context);
        populateVectorUnrollPatterns(patterns, /*support dot prodcut*/ false);
        if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // Lower reduction-unrolled vector contract ops. Such contract ops have
      // their reduction dimensions all be one, so we can convert them into
      // elementwise ops.
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet patterns(context);
        auto options = vector::VectorTransformsOptions().setVectorTransformsOptions(
            vector::VectorContractLowering::ParallelArith);
        vector::populateVectorContractLoweringPatterns(patterns, options);
        // The pattern can generate transpose ops. Try to fold it if possible to
        // avoid lowering them into extract/insert later.
        vector::TransposeOp::getCanonicalizationPatterns(patterns, context);
        // It also generates broadcast/extract ops. Clean up them too.
        vector::BroadcastOp::getCanonicalizationPatterns(patterns, context);
        vector::ExtractOp::getCanonicalizationPatterns(patterns, context);
        if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // Now lower vector transpose given we have handled vector patterns that may
      // generate transpose ops in previous steps. This converts transpose ops
      // into extract and insert pairs, in preparation of further transformations
      // to canonicalize/cancel.
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet patterns(context);
        auto options = vector::VectorTransformsOptions().setVectorTransposeLowering(
            vector::VectorTransposeLowering::Shuffle1D);
        vector::populateVectorTransposeLoweringPatterns(patterns, options);
        vector::populateVectorShapeCastLoweringPatterns(patterns);
        if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      //===----------------------------------------------------------------------===//
      // Next run canonicalization to cast away leading size-1 dimensions. They
      // can be generated from vector unrolling and generally cause issues to
      // cancel corresponding read/write or insert/extract op pairs. This also
      // need to happen before hoisting, where we would make certain vectors loop
      // carried. Once that's done, it's hard to handle the leading size-1
      // dimensions across regions.
      //===----------------------------------------------------------------------===//
      {
        RewritePatternSet patterns(context);

        // We need to pull in casting way leading one dims to allow cancelling
        // some read/write ops.
        vector::populateCastAwayVectorLeadingOneDimPatterns(patterns);

        // We may have vector.insert_strided_slice inserting 1-D native vectors
        // into n-D larger vectors with the above. Break that down too. This is a
        // companion transformation of unrolling.
        vector::populateVectorInsertExtractStridedSliceDecompositionPatterns(patterns);
        vector::ExtractOp::getCanonicalizationPatterns(patterns, context);

        // Trimming leading unit dims may generate broadcast/shape_cast ops. Clean
        // them up.
        vector::BroadcastOp::getCanonicalizationPatterns(patterns, context);
        vector::ShapeCastOp::getCanonicalizationPatterns(patterns, context);

        vector::TransferReadOp::getCanonicalizationPatterns(patterns, context);
        vector::TransferWriteOp::getCanonicalizationPatterns(patterns, context);
        populateVectorTransferTensorSliceTransforms(patterns);

        if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(patterns)))) {
          return signalPassFailure();
        }
      }

      return;

      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------
      // -----------------------------------------------------------------------------------------------

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
        auto options =
            mlir::vector::VectorTransformsOptions()
                .setVectorTransformsOptions(mlir::vector::VectorContractLowering::OuterProduct)
                .setVectorTransposeLowering(mlir::vector::VectorTransposeLowering::Shuffle1D);
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
                .setVectorTransposeLowering(mlir::vector::VectorTransposeLowering::Shuffle1D);
        mlir::vector::populateVectorBroadcastLoweringPatterns(patterns);
        mlir::vector::populateVectorContractLoweringPatterns(patterns, options);
        mlir::vector::populateVectorMultiReductionLoweringPatterns(
            patterns, vector::VectorMultiReductionLowering::InnerParallel);
        mlir::vector::populateVectorTransposeLoweringPatterns(patterns, options);

        // avx2 shuffle
        // FIXME error: couldn't allocate output register for constraint 'x'
        // auto avx2LoweringOptions = x86vector::avx2::LoweringOptions().setTransposeOptions(
        //     x86vector::avx2::TransposeLoweringOptions().lower4x8xf32(true).lower8x8xf32(true));
        // x86vector::avx2::populateSpecializedTransposeLoweringPatterns(patterns,
        // avx2LoweringOptions,
        //                                                               /*benefit=*/10);

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