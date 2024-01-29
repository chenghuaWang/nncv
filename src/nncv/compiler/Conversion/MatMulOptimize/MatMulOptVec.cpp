#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptVec.hpp"
#include "mlir/Dialect/Tensor/Transforms/Transforms.h"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
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
#define GEN_PASS_DEF_MATMULOPTIMIZATION_VEC
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
namespace matmul_optimize {

namespace {

class MatMulOptimizationVec : public impl::MatMulOptimization_VecBase<MatMulOptimizationVec> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    if (m_enableNvGPU) {
    } else {
      // Step 1. Tiling
      IRRewriter rewriter(&getContext());
      getOperation()->walk([&](linalg::MatmulOp op) {
        // This pass should work on tensor.
        if (op.hasBufferSemantics()) return signalPassFailure();
        // [Linalg + Tensor] High Level Tile
        llvm::SmallVector<OpFoldResult> tiles(op.getNumLoops());
        auto loop0 = ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTile.loop0;
        auto loop1 = ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTile.loop1;
        auto loop2 = ::nncv::compiler::utils::PlatformCtx::getInstance().MatMulTile.loop2;

        tiles[0] = mlir::getAsIndexOpFoldResult(rewriter.getContext(), loop0);
        tiles[1] = mlir::getAsIndexOpFoldResult(rewriter.getContext(), loop1);
        tiles[2] = mlir::getAsIndexOpFoldResult(rewriter.getContext(), loop2);

        OpBuilder::InsertionGuard guard(rewriter);
        rewriter.setInsertionPoint(op);

        // TODO tile_using_for's c++ API Check
        auto tiledResults = mlir::linalg::tileToForallOpUsingTileSizes(
            rewriter, mlir::cast<TilingInterface>(op.getOperation()), tiles, std::nullopt);
        rewriter.replaceOp(op, tiledResults->tileOp->getResults());
      });
    }

    // Step 2.
    mlir::RewritePatternSet patterns(&getContext());
    linalg::populateLinalgTilingCanonicalizationPatterns(patterns);
    if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
      signalPassFailure();
    }
  }

  void setNvGPU(bool flag = true) { m_enableNvGPU = flag; }
  bool isNvGPUEnable() { return m_enableNvGPU; }

 private:
  bool m_enableNvGPU = false;
};

}  // namespace

std::unique_ptr<mlir::Pass> createMatMulOptimizationVecPass(bool flag) {
  auto res = std::make_unique<MatMulOptimizationVec>();
  res->setNvGPU(flag);
  return res;
}
}  // namespace matmul_optimize
}  // namespace nncv
}  // namespace mlir