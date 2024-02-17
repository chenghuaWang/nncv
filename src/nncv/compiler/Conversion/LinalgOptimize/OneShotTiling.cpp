#include "nncv/compiler/Conversion/LinalgOptimize/OneShotTiling.hpp"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/IR/LinalgInterfaces.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/Linalg/TransformOps/LinalgTransformOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/SCF/Transforms/TileUsingInterface.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Transform/IR/TransformDialect.h"
#include "mlir/Dialect/Transform/IR/TransformInterfaces.h"
#include "mlir/Dialect/Vector/IR/VectorOps.h"

#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "nncv/compiler/Optimizer/TileSolver.hpp"
#include "nncv/compiler/TransformCommon/Common.hpp"

namespace mlir::nncv {
#define GEN_PASS_DEF_ONESHOTTILING
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {

namespace {

template<typename PatternTy, typename... Args>
static FailureOr<linalg::LinalgOp> tryApply(Operation* operation, Args&&... args) {
  // Check if the given operation has the type expected by the pattern.
  using OpTy = typename llvm::function_traits<
      decltype(&PatternTy::returningMatchAndRewrite)>::template arg_t<0>;
  auto op = dyn_cast<OpTy>(operation);
  if (!op) return failure();

  // Apply the pattern directly to the op.
  PatternTy pattern(operation->getContext(), std::forward<Args>(args)...);
  // We want to discourage direct use of PatternRewriter in APIs but In this
  // very specific case, an IRRewriter is not enough.
  struct TrivialPatternRewriter : public PatternRewriter {
   public:
    explicit TrivialPatternRewriter(MLIRContext* context) : PatternRewriter(context) {}
  };
  TrivialPatternRewriter rewriter(operation->getContext());
  rewriter.setInsertionPoint(operation);
  auto result = pattern.returningMatchAndRewrite(op, rewriter);
  if (failed(result)) return failure();
  return cast<linalg::LinalgOp>(result->getOperation());
}

[[maybe_unused]] FailureOr<mlir::linalg::LinalgOp> decomposeConv2d(linalg::LinalgOp target){
#define DOWNSCALE(trans)                                             \
  {                                                                  \
    FailureOr<mlir::linalg::LinalgOp> res = tryApply<trans>(target); \
    if (succeeded(res)) { return res; }                              \
  }
// clang-format off
#define DOWNSCALE_CALL(a, b) linalg::DownscaleSizeOneWindowed2DConvolution<a, b>
#define DOWNSCALE_NORMAL(a, b) DOWNSCALE(DOWNSCALE_CALL(a, b))

  DOWNSCALE_NORMAL(linalg::Conv2DNhwcHwcfOp, linalg::Conv1DNwcWcfOp)
  DOWNSCALE_NORMAL(linalg::Conv2DNchwFchwOp, linalg::Conv1DNcwFcwOp)
  DOWNSCALE_NORMAL(linalg::PoolingNhwcSumOp, linalg::PoolingNwcSumOp)
  DOWNSCALE_NORMAL(linalg::PoolingNchwSumOp, linalg::PoolingNcwSumOp)
  DOWNSCALE_NORMAL(linalg::PoolingNhwcMaxOp, linalg::PoolingNwcMaxOp)
  DOWNSCALE_NORMAL(linalg::PoolingNhwcMaxUnsignedOp, linalg::PoolingNwcMaxUnsignedOp)
  DOWNSCALE_NORMAL(linalg::PoolingNhwcMinOp, linalg::PoolingNwcMinOp)
  DOWNSCALE_NORMAL(linalg::PoolingNhwcMinUnsignedOp, linalg::PoolingNwcMinUnsignedOp)
  DOWNSCALE_NORMAL(linalg::PoolingNchwMaxOp, linalg::PoolingNcwMaxOp)
  DOWNSCALE(linalg::DownscaleDepthwiseConv2DNhwcHwcOp)
  DOWNSCALE(linalg::DownscaleConv2DOp)
#undef DOWNSCALE_NORMAL
#undef DOWNSCALE_CALL
#undef DOWNSCALE

    // clang-format on
}

llvm::SmallVector<scf::ForOp> toScfForOp(llvm::SmallVector<mlir::Operation*>& ops) {
  llvm::SmallVector<scf::ForOp> res;
  for (auto item : ops) res.emplace_back(mlir::cast<mlir::scf::ForOp>(item));
  return res;
}

class OneShotTilingPass : public impl::OneShotTilingBase<OneShotTilingPass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry.insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                    mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect,
                    mlir::transform::TransformDialect>();
  }

  void runOnOperation() override {
    IRRewriter rewriter(&getContext());
    auto& tileSolver = ::nncv::compiler::optimizer::TileSolver::getInstance();
    auto tileDict = tileSolver.getDict();

    getOperation().walk([&](mlir::linalg::LinalgOp op) {
      if (tileSolver.getLinkToDict().find(op) == tileSolver.getLinkToDict().end()) return;
    });

    for (auto& item : tileDict) {
      auto node = item.first;
      auto options = item.second;

      auto curOp = node.getOp();
      for (auto& tileLevel : options.tileSizes) {
        auto tilingInterface = dyn_cast<TilingInterface>(curOp);

        llvm::SmallVector<OpFoldResult> sizes;
        for (auto idx : tileLevel) sizes.push_back(rewriter.getIndexAttr(idx));

        mlir::scf::SCFTilingOptions tilingOptions;
        tilingOptions.setTileSizes(sizes);

        // tile ops
        // TODO not in parallel for now.
        auto tiledOps = mlir::scf::tileUsingSCFForOp(rewriter, tilingInterface, tilingOptions);
        rewriter.replaceOp(curOp, tiledOps->replacements);

        curOp = tiledOps->tiledOps[0];
      }
    }

    // Canonicalize
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::populateLinalgTilingCanonicalizationPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

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
};
}  // namespace

std::unique_ptr<mlir::Pass> createOneShotTilingPass() {
  return std::make_unique<OneShotTilingPass>();
}

}  // namespace mlir::nncv