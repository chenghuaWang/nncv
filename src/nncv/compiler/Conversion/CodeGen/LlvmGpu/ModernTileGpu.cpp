// GPU Tiling
// 1. SGEMM
// For SGEMM, I adopt a static tiling method here. By using nvidia's three threads' level(kernel:
// grid->block->thread), each SGEMM kernel will be tiled to blocks(128x128), each block will launch
// 256 threads(16x16). For now, occupacy of registers is not fine tunned.
// More infomation about how to optimize SGEMM can be found at:
// (1) MegEngine's tech report: https://zhuanlan.zhihu.com/p/410278370
// (2) Q's pratice: https://zhuanlan.zhihu.com/p/442930482
// (3) CUDA guide: https://docs.nvidia.com/cuda/cuda-c-programming-guide/
//
// 2. Elementwise
//
// 3. Convolution like Interface
//
//
#include "nncv/compiler/Conversion/CodeGen/LlvmGpu/ModernTileGpu.hpp"
#include "llvm/Support/ErrorHandling.h"
#include "mlir/Dialect/Linalg/TransformOps/LinalgTransformOps.h"
#include "mlir/Dialect/Linalg/Transforms/Hoisting.h"
#include "mlir/Dialect/Linalg/Transforms/Transforms.h"
#include "mlir/Dialect/SCF/Transforms/TileUsingInterface.h"
#include "mlir/Dialect/Transform/LoopExtension/LoopExtensionOps.h"
#include "mlir/Dialect/Vector/Transforms/LoweringPatterns.h"
#include "mlir/Dialect/Vector/Transforms/VectorRewritePatterns.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/Visitors.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Interfaces/TilingInterface.h"
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
#define GEN_PASS_DEF_MODERNTILEGPU
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

struct Simt {
  SmallVector<int64_t> blockDims;
  SmallVector<int64_t> threadDims;
  SmallVector<int64_t> loopsInThreadDims;
  SmallVector<mlir::Operation*> blockLevelLoops = {nullptr};
  SmallVector<mlir::Operation*> threadLevelLoops = {nullptr};
  SmallVector<mlir::Operation*> loopsInEachThreads = {nullptr};
};

struct ModernMatMulTileOptions {
  SmallVector<SmallVector<int64_t>> tileSizes;
  SmallVector<bool> canForall;
};

// Blocks level [128, 128, 0]
// Threads level [16, 16, 0]
// register level [0, 0, 4]
// Note: the register level should be modified if use Tensor Core's Gemm intr.
ModernMatMulTileOptions getMatMulTileOptions(mlir::Operation* op) {
  ModernMatMulTileOptions ret;
  ret.tileSizes.push_back({128, 128, 0});
  ret.tileSizes.push_back({16, 16, 0});
  ret.tileSizes.push_back({0, 0, 4});
  ret.canForall = {true, true, false};
  return ret;
}

// MatMul tiling will invlove vector.mask, be careful when lowering vector.mask. All three level
// tiling can be made parallel.
// ! Matmul's for loops will not be peeled.
bool tileMatMulUseScf(IRRewriter& rewriter, mlir::Operation* op, bool forall) {
  auto moptions = getMatMulTileOptions(op);
  auto curOp = op;
  for (int i = 0; i < 3; ++i) {
    mlir::scf::SCFTilingOptions options;
    SmallVector<mlir::OpFoldResult> sizes;
    for (size_t kk = 0; kk < moptions.tileSizes[i].size(); ++kk) {
      sizes.push_back(rewriter.getIndexAttr(moptions.tileSizes[i][kk]));
    }
    options.setTileSizes(sizes);
    auto tileInterface = mlir::dyn_cast<mlir::TilingInterface>(curOp);
    if (moptions.canForall[i]) {
      rewriter.setInsertionPoint(curOp);
      auto result = mlir::linalg::tileToForallOpUsingTileSizes(rewriter, tileInterface, sizes,
                                                               /*mapping*/ std::nullopt);
      if (failed(result)) return false;
      rewriter.replaceOp(curOp, result->tileOp->getResults());
      curOp = result->tiledOp;
    } else {
      auto result = mlir::scf::tileUsingSCFForOp(rewriter, tileInterface, options);
      if (failed(result)) return false;
      rewriter.replaceOp(curOp, result->replacements);
      curOp = result->tiledOps[0];
    }
  }
  return true;
}

void emitTileFailedError(bool isOk, mlir::Operation* op) {
  if (!isOk) {
    printf("[ Warn ] When tiling %s op, failed.\n", op->getName().getStringRef().str().c_str());
  }
}

class ModernTileGpuPass final : public impl::ModernTileGpuBase<ModernTileGpuPass> {
  void runOnOperation() override {}
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createModernOneShotTileAllGpuPass() {
  return std::make_unique<ModernTileGpuPass>();
}

}  // namespace mlir::nncv
