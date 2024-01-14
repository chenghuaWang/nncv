#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/Transforms/Transforms.h"
#include "mlir/Dialect/Tensor/Transforms/Transforms.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/PassDetails.hpp"
#include "nncv/compiler/Dialects/NncvFrontend/Transforms/Passes.hpp"
#include "mlir/IR/Iterators.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Transforms/TopologicalSortUtils.h"

namespace mlir::nncv {

static std::optional<OpOperand*> getFusableUse(Operation* op, DominanceInfo& dominanceInfo) {
  auto uses = op->getUses();
  for (OpOperand& source : uses) {
    Operation* sourceOp = source.getOwner();
    bool dominatesAllUsers = true;
    for (OpOperand& target : uses) {
      Operation* targetOp = target.getOwner();
      if (!dominanceInfo.dominates(sourceOp, targetOp)) {
        dominatesAllUsers = false;
        break;
      }
    }
    if (dominatesAllUsers) { return &source; }
  }
  return std::nullopt;
}

static bool areFusableOps(MLIRContext* context, OpOperand* fusedOperand) {
  Operation* producerOp = fusedOperand->get().getDefiningOp();
  Operation* consumerOp = fusedOperand->getOwner();
  if (!producerOp) return false;

  if (llvm::all_of(producerOp->getResultTypes(), [](Type t) {
        if (t.isInteger(1)) return true;
        if (auto shapedType = llvm::dyn_cast<ShapedType>(t)) {
          if (shapedType.getElementType().isInteger(1)) return true;
        }
        return false;
      })) {
    return true;
  }

  if (auto linalgConsumerOp = dyn_cast<linalg::LinalgOp>(consumerOp)) {
    if (!llvm::all_of(linalgConsumerOp.getIndexingMapsArray(),
                      [](AffineMap map) { return map.isProjectedPermutation(); })) {
      return false;
    }
  }

  Block& body = producerOp->getRegion(0).front();
  if (std::begin(body)->hasTrait<OpTrait::IsTerminator>()) return true;
  if (llvm::all_of(body.getArguments(), [](BlockArgument arg) { return arg.use_empty(); })) {
    return true;
  }

  if (!producerOp->hasOneUse()) { return false; }

  if (auto linalgConsumerOp = dyn_cast<linalg::LinalgOp>(consumerOp)) {
    if (linalgConsumerOp.getNumParallelLoops() == linalgConsumerOp.getNumLoops()) { return true; }
    if (linalgConsumerOp.getNumReductionLoops() != 1
        || !linalgConsumerOp.getMatchingIndexingMap(fusedOperand).isPermutation()) {
      return false;
    }
    return true;
  }

  return false;
}

static OpOperand* getFirstUseInConsumer(Operation* producer, Operation* consumer) {
  for (OpOperand& opOperand : consumer->getOpOperands()) {
    if (opOperand.get().getDefiningOp() == producer) { return &opOperand; }
  }
  return nullptr;
}

static SmallVector<OpOperand*> getAllUsesInConsumer(Operation* producer, Operation* consumer) {
  SmallVector<OpOperand*> allUses;
  for (OpOperand& opOperand : consumer->getOpOperands()) {
    if (opOperand.get().getDefiningOp() == producer) { allUses.push_back(&opOperand); }
  }
  return allUses;
}

static LogicalResult doMultiUseFusion(Operation* rootOp, llvm::SetVector<Operation*>& fusableOps,
                                      RewriterBase& rewriter) {
  SmallVector<Operation*> fusedOpsVec = llvm::to_vector(fusableOps);
  mlir::computeTopologicalSorting(fusedOpsVec);

  Operation* consumerOp = rootOp;
  OpBuilder::InsertionGuard g(rewriter);
  for (Operation* producerOp : llvm::reverse(fusedOpsVec)) {
    // Fuse all uses from producer -> consumer. It has been checked
    // before that all uses are fusable.
    while (OpOperand* fusedOperand = getFirstUseInConsumer(producerOp, consumerOp)) {
      rewriter.setInsertionPoint(consumerOp);
      FailureOr<linalg::ElementwiseOpFusionResult> fusionResult =
          linalg::fuseElementwiseOps(rewriter, fusedOperand);
      if (failed(fusionResult)) {
        return rewriter.notifyMatchFailure(consumerOp, "failed to fuse with producer");
      }
      for (auto replacement : fusionResult->replacements) {
        rewriter.replaceUsesWithIf(replacement.first, replacement.second, [&](OpOperand& use) {
          return use.getOwner() != fusionResult->fusedOp && fusableOps.count(use.getOwner()) == 0;
        });
      }
      consumerOp = fusionResult->fusedOp;
      if (failed(cast<linalg::GenericOp>(consumerOp).verify())) {
        return consumerOp->emitOpError("failed to verify op");
      }
    }
  }
  return success();
}

static FailureOr<unsigned> fuseMultiUseProducers(Operation* funcOp, MLIRContext* context,
                                                 DominanceInfo& dominanceInfo) {
  OpBuilder builder(context);
  llvm::MapVector<Operation*, llvm::SetVector<Operation*>> fusedOps;
  DenseMap<Operation*, Operation*> opToRootMap;
  funcOp->walk<WalkOrder::PostOrder, ReverseIterator>([&](linalg::GenericOp genericOp) {
    // 1. Only look at all parallel consumers.
    if (genericOp.getNumLoops() != genericOp.getNumParallelLoops()) { return; }

    Operation* fusableProducer = nullptr;
    for (OpOperand& operand : genericOp->getOpOperands()) {
      // 2. Only fuse with `linalg.generic` producers that arent
      //    already part of another fusion group.
      auto producer = dyn_cast_or_null<linalg::GenericOp>(operand.get().getDefiningOp());
      if (!producer || opToRootMap.count(producer)) { continue; }

      // 3. For now do not fuse with ops in another block.
      if (producer->getBlock() != genericOp->getBlock()) { continue; }

      // 4. Basic fusability checks.
      if (!linalg::areElementwiseOpsFusable(&operand)) { continue; }

      // 5. Only consider all parallel `producer` with same iteration space
      //    as the consumer.
      if (producer.getNumLoops() != producer.getNumParallelLoops()
          || genericOp.getNumLoops() != producer.getNumLoops()) {
        continue;
      }

      // 6. Check that the `genericOp` dominates all uses of `producer`.
      std::optional<OpOperand*> fusableUse = getFusableUse(producer, dominanceInfo);
      if (!fusableUse || fusableUse.value()->getOwner() != genericOp) { continue; }

      // 7. All uses from `producer` -> `consumer` need to be fusable.
      //    Without this the `producer` is still live, and there is no
      //    advantage to do the fusion.
      if (llvm::any_of(getAllUsesInConsumer(producer, genericOp),
                       [&](OpOperand* use) { return !linalg::areElementwiseOpsFusable(use); })) {
        continue;
      }

      fusableProducer = producer;
      break;
    }
    if (!fusableProducer) return;

    // If the `genericOp` is already part of a fusion group, just add the
    // the `fusableProducer` to the same group.
    llvm::SetVector<Operation*>& fusedOpSet = fusedOps[genericOp];
    fusedOpSet.insert(fusableProducer);
    opToRootMap[fusableProducer] = genericOp;
    return;
  });

  if (fusedOps.empty()) { return 0; }

  IRRewriter rewriter(context);
  for (auto it = fusedOps.rbegin(), ie = fusedOps.rend(); it != ie; ++it) {
    if (failed(doMultiUseFusion(it->first, it->second, rewriter))) {
      return funcOp->emitOpError("failed multi use fusion");
    }
  }

  RewritePatternSet fusionPatterns(context);
  linalg::populateEraseUnusedOperandsAndResultsPatterns(fusionPatterns);
  if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(fusionPatterns)))) {
    return funcOp->emitOpError("multi use producer -> consumer fusion failed");
  }
  return fusedOps.size();
}

namespace {
class FusionTensorOpsPass : public FusionTensorOpsBase<FusionTensorOpsPass> {
 public:
  FusionTensorOpsPass(bool fuseMultiUse, unsigned multiUseFusionIteration) {
    this->fuseMultiUse = fuseMultiUse;
    this->multiUseFusionIteration = multiUseFusionIteration;
  }
  FusionTensorOpsPass(const FusionTensorOpsPass& pass)
      : FusionTensorOpsPass(pass.fuseMultiUse, pass.multiUseFusionIteration) {}

  void getDependentDialects(DialectRegistry& registry) const override {
    registry.insert<mlir::affine::AffineDialect, mlir::arith::ArithDialect,
                    mlir::linalg::LinalgDialect, mlir::math::MathDialect>();
  }

  void runOnOperation() override {
    Operation* funcOp = getOperation();
    MLIRContext* context = funcOp->getContext();
    //===----------------------------------------------------------------------===//
    // fuse element op
    //===----------------------------------------------------------------------===//
    {
      RewritePatternSet fusionPatterns(&getContext());
      mlir::linalg::ControlFusionFn fuseElementwiseOpsControlFn = [&](OpOperand* fusedOperand) {
        Operation* producer = fusedOperand->get().getDefiningOp();
        Operation* consumer = fusedOperand->getOwner();

        constexpr int64_t kMaxOperandCount = 32;
        DenseSet<Value> operands;
        operands.insert(producer->operand_begin(), producer->operand_end());
        operands.insert(consumer->operand_begin(),
                        std::next(consumer->operand_begin(), fusedOperand->getOperandNumber()));
        operands.insert(std::next(consumer->operand_begin(), fusedOperand->getOperandNumber() + 1),
                        consumer->operand_end());
        if (operands.size() >= kMaxOperandCount) return false;

        return areFusableOps(context, fusedOperand);
      };
      linalg::populateElementwiseOpsFusionPatterns(fusionPatterns, fuseElementwiseOpsControlFn);

      // Always fold reshape by expansion.
      linalg::ControlFusionFn fuseByExpansionControlFn = [](OpOperand* fusedOperand) {
        Operation* producer = fusedOperand->get().getDefiningOp();

        if (auto producerGenericOp = dyn_cast<linalg::GenericOp>(producer)) {
          return producerGenericOp->hasOneUse();
        }
        return true;
      };
      linalg::populateFoldReshapeOpsByExpansionPatterns(fusionPatterns, fuseByExpansionControlFn);

      // Constant fold Linalg operations.
      auto constantFoldControlFn = [](OpOperand* fusedOperand) {
        Operation* producer = fusedOperand->get().getDefiningOp();
        if (auto shapedType = dyn_cast<ShapedType>(fusedOperand->get().getType())) {
          if (shapedType.hasStaticShape()
              && shapedType.getNumElements() > P_LINALG_MAX_CONSTANT_FOLD_ELEMENTS) {
            return false;
          }
        }
        return producer->hasOneUse();
      };

      linalg::populateConstantFoldLinalgOperations(fusionPatterns, constantFoldControlFn);
      affine::AffineApplyOp::getCanonicalizationPatterns(fusionPatterns, context);
      linalg::GenericOp::getCanonicalizationPatterns(fusionPatterns, context);
      tensor::ExpandShapeOp::getCanonicalizationPatterns(fusionPatterns, context);
      tensor::populateFoldTensorEmptyPatterns(fusionPatterns);
      tensor::CollapseShapeOp::getCanonicalizationPatterns(fusionPatterns, context);
      context->getLoadedDialect<linalg::LinalgDialect>()->getCanonicalizationPatterns(
          fusionPatterns);
      memref::populateResolveRankedShapedTypeResultDimsPatterns(fusionPatterns);

      GreedyRewriteConfig rewriteConfig;
      rewriteConfig.maxIterations = GreedyRewriteConfig::kNoLimit;
      if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(fusionPatterns), rewriteConfig))) {
        funcOp->emitError("failed to apply fusion patterns");
        return signalPassFailure();
      }
    }

    //===----------------------------------------------------------------------===//
    // fuse collapsing
    //===----------------------------------------------------------------------===//
    {
      linalg::ControlFusionFn fuseByCollapsingControlFn = [](OpOperand* fusedOperand) {
        Operation* producer = fusedOperand->get().getDefiningOp();
        Operation* consumer = fusedOperand->getOwner();

        if (auto linalgConsumerOp = dyn_cast<linalg::LinalgOp>(consumer)) {
          if (linalg::isaContractionOpInterface(linalgConsumerOp)) { return false; }
        }

        auto reshapeOp = dyn_cast<tensor::ExpandShapeOp>(producer);
        if (!reshapeOp) { return true; }

        return reshapeOp.getSrc().getDefiningOp<linalg::LinalgOp>() != nullptr;
      };

      RewritePatternSet collapsingReshapePatterns(&getContext());
      linalg::populateFoldReshapeOpsByCollapsingPatterns(collapsingReshapePatterns,
                                                         fuseByCollapsingControlFn);
      tensor::CollapseShapeOp::getCanonicalizationPatterns(collapsingReshapePatterns, context);
      tensor::ExpandShapeOp::getCanonicalizationPatterns(collapsingReshapePatterns, context);
      tensor::populateFoldTensorEmptyPatterns(collapsingReshapePatterns);
      memref::populateResolveRankedShapedTypeResultDimsPatterns(collapsingReshapePatterns);
      if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(collapsingReshapePatterns)))) {
        funcOp->emitError("failed to apply collapsing reshape patterns");
        return signalPassFailure();
      }
    }

    //===----------------------------------------------------------------------===//
    // fold
    //===----------------------------------------------------------------------===//
    {
      RewritePatternSet opFoldingPatterns(&getContext());
      tensor::populateFoldTensorEmptyPatterns(opFoldingPatterns);
      if (failed(applyPatternsAndFoldGreedily(funcOp, std::move(opFoldingPatterns)))) {
        funcOp->emitError("failed to apply op folding patterns");
        return signalPassFailure();
      }
    }

    for (auto i : llvm::seq<unsigned>(0, multiUseFusionIteration)) {
      (void)i;
      auto& dominanceInfo = getAnalysis<DominanceInfo>();
      FailureOr<unsigned> numOfFusableCandidates =
          fuseMultiUseProducers(funcOp, context, dominanceInfo);
      if (failed(numOfFusableCandidates)) {
        funcOp->emitError("failed to fuse multi-use producers");
        return signalPassFailure();
      }
      if (numOfFusableCandidates.value() == 0) break;
    }
  }
};
}  // namespace

std::unique_ptr<InterfacePass<FunctionOpInterface>> createFusionTensorOpsPass(
    bool fuseMultiUse, unsigned multiUseFusionIteration) {
  return std::make_unique<FusionTensorOpsPass>(fuseMultiUse, multiUseFusionIteration);
}
};  // namespace mlir::nncv
