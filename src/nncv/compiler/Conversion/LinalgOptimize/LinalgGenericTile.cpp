#include "nncv/compiler/Conversion/LinalgOptimize/LinalgGenericTile.hpp"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

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

namespace mlir::nncv {
#define GEN_PASS_DEF_LINALGGENERICTILE
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {

namespace {
class LinalgGenericTilePass : public impl::LinalgGenericTileBase<LinalgGenericTilePass> {
 public:
  void getDependentDialects(mlir::DialectRegistry& registry) const override {
    registry
        .insert<mlir::BuiltinDialect, mlir::func::FuncDialect, mlir::affine::AffineDialect,
                mlir::tensor::TensorDialect, mlir::arith::ArithDialect, mlir::scf::SCFDialect>();
  }

  void runOnOperation() override {
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::populateFuseTensorPadWithProducerLinalgOpPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }

    IRRewriter rewriter(&getContext());
    if (m_enableNvGPU) {
    } else {
      llvm::SmallVector<mlir::Operation*> candidates;
      getOperation()->walk([&](mlir::linalg::GenericOp op) {
        // linalg generic tile like Matmul tiling, I adopt [[], [], []] 3 levels tilings here.
        if (op.hasBufferSemantics()) return signalPassFailure();
        candidates.emplace_back(op);
      });

      for (auto _op : candidates) {
        // The linalg op below will not tiled
        // a. Matmul: it will be tiled before this pass
        // b. Any conv2d: also will be tiled before this pass
        // c. fill: ?
        if (mlir::isa<mlir::linalg::MatmulOp>(_op) || mlir::isa<mlir::linalg::FillOp>(_op)
            || linalg::vectorizeOpPrecondition(_op).failed()) {
          continue;
        }

        FailureOr<linalg::TiledLinalgOp> tiledOps;
        mlir::linalg::GenericOp op = llvm::dyn_cast<linalg::GenericOp>(_op);

        // TODO make the code below more gorgeous
        if (op.getNumParallelLoops() == 3) {
          ///<------------------------ Step 1.1. Tilling out loop
          {
            linalg::LinalgTilingOptions tileOption;
            tileOption.setTileSizes(::nncv::compiler::utils::PlatformCtx::getInstance()
                                        .LinalgGenericTileCpu.outerLevelLoops);

            OpBuilder::InsertionGuard guard(rewriter);
            rewriter.setInsertionPoint(op);
            tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
            rewriter.replaceOp(op, tiledOps->tensorResults);

            op = mlir::cast<mlir::linalg::GenericOp>(tiledOps->op);
          }

          ///<------------------------ Step 1.2. Tilling inner loop
          {
            linalg::LinalgTilingOptions tileOption;
            tileOption.setTileSizes(::nncv::compiler::utils::PlatformCtx::getInstance()
                                        .LinalgGenericTileCpu.innerLevelLoops);

            OpBuilder::InsertionGuard guard0(rewriter);
            rewriter.setInsertionPoint(op);

            tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
            rewriter.replaceOp(op, tiledOps->tensorResults);

            op = mlir::cast<mlir::linalg::GenericOp>(tiledOps->op);
          }

          ///<------------------------ Step 1.3. Tilling register loop
          {
            linalg::LinalgTilingOptions tileOption;
            tileOption.setTileSizes(::nncv::compiler::utils::PlatformCtx::getInstance()
                                        .LinalgGenericTileCpu.registerLevelLoops);

            OpBuilder::InsertionGuard guard(rewriter);
            rewriter.setInsertionPoint(op);

            FailureOr<linalg::TiledLinalgOp> tiledOps =
                linalg::tileLinalgOp(rewriter, op, tileOption);
            rewriter.replaceOp(op, tiledOps->tensorResults);
          }
        } else if (op.getNumParallelLoops() == 2) {
          ///<------------------------ Step 1.1. Tilling out loop
          {
            linalg::LinalgTilingOptions tileOption;
            tileOption.setTileSizes({1, 8});

            OpBuilder::InsertionGuard guard(rewriter);
            rewriter.setInsertionPoint(op);
            tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
            rewriter.replaceOp(op, tiledOps->tensorResults);

            op = mlir::cast<mlir::linalg::GenericOp>(tiledOps->op);
          }
        } else if (op.getNumParallelLoops() == 1) {
          ///<------------------------ Step 1.1. Tilling out loop
          {
            linalg::LinalgTilingOptions tileOption;
            tileOption.setTileSizes({8});

            OpBuilder::InsertionGuard guard(rewriter);
            rewriter.setInsertionPoint(op);
            tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
            rewriter.replaceOp(op, tiledOps->tensorResults);

            op = mlir::cast<mlir::linalg::GenericOp>(tiledOps->op);
          }
        }
      }

      // llvm::SmallVector<mlir::Operation*> fillCandidates;
      // getOperation()->walk([&](mlir::linalg::FillOp op) {
      //   if (op.hasBufferSemantics()) return signalPassFailure();
      //   fillCandidates.emplace_back(op);
      // });

      // for (auto _op : fillCandidates) {
      //   FailureOr<linalg::TiledLinalgOp> tiledOps;
      //   mlir::linalg::FillOp op = llvm::dyn_cast<linalg::FillOp>(_op);

      //   ///<------------------------ Step 1.1. Tilling out loop
      //   {
      //     linalg::LinalgTilingOptions tileOption;
      //     tileOption.setTileSizes({1, 1, 8, 8});

      //     OpBuilder::InsertionGuard guard(rewriter);
      //     rewriter.setInsertionPoint(op);
      //     tiledOps = linalg::tileLinalgOp(rewriter, op, tileOption);
      //     rewriter.replaceOp(op, tiledOps->tensorResults);

      //     op = mlir::cast<mlir::linalg::FillOp>(tiledOps->op);
      //   }
      // }
    }
    {
      mlir::RewritePatternSet patterns(&getContext());
      mlir::linalg::populateLinalgTilingCanonicalizationPatterns(patterns);
      if (failed(mlir::applyPatternsAndFoldGreedily(getOperation(), std::move(patterns)))) {
        signalPassFailure();
      }
    }
  }

  void setNvGPU(bool flag = true) { m_enableNvGPU = flag; }
  bool isNvGPUEnable() { return m_enableNvGPU; }

 private:
  bool m_enableNvGPU = false;
};
}  // namespace

std::unique_ptr<mlir::Pass> createLinalgGenericTilePass(bool flag) {
  auto res = std::make_unique<LinalgGenericTilePass>();
  res->setNvGPU(flag);
  return res;
}

}  // namespace nncv
}  // namespace mlir