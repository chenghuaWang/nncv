#include "nncv/compiler/Conversion/CodeGen/Advance/TileAndDispatch.hpp"
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
#define GEN_PASS_DEF_ADVANCEDTILEANDDISPATCH
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir::nncv {
namespace {

struct AdvTileOptions {
  SmallVector<SmallVector<int64_t>> tileSizes;
  SmallVector<bool> canForall;
};

bool isGenericAllParallel(mlir::Operation* op) {
  auto linalgOp = mlir::cast<mlir::linalg::GenericOp>(op);
  auto iterTypes = linalgOp.getIteratorTypesArray();
  for (auto item : iterTypes) {
    if (item == utils::IteratorType::reduction) return false;
  }
  return true;
}

bool isOneReductionAtLast(mlir::Operation* op) {
  auto linalgOp = mlir::cast<mlir::linalg::GenericOp>(op);
  auto iterTypes = linalgOp.getIteratorTypesArray();
  for (size_t i = 0; i < iterTypes.size() - 1; ++i) {
    if (iterTypes[i] == utils::IteratorType::reduction) return false;
  }
  if (iterTypes[iterTypes.size() - 1] == utils::IteratorType::reduction) return true;
  return false;
}

std::pair<bool, int> isAllParallelBeforeReduction(mlir::Operation* op) {
  bool meetR = false;
  int pos = 0;
  auto linalgOp = mlir::cast<mlir::linalg::GenericOp>(op);
  auto iterTypes = linalgOp.getIteratorTypesArray();
  int cnt = 0;
  for (auto& item : iterTypes) {
    if (item == utils::IteratorType::reduction && !meetR) {
      meetR = true;
      pos = cnt;
    }
    if (meetR && item == utils::IteratorType::parallel) return std::make_pair(false, pos);
    cnt++;
  }
  return std::make_pair(true, pos);
}

AdvTileOptions getGenericTileOptions(mlir::Operation* op) {
  AdvTileOptions ret;

  auto linalgOp = mlir::cast<mlir::linalg::GenericOp>(op);
  auto iterTypes = linalgOp.getIteratorTypesArray();

  // case 1. all parallel
  if (isGenericAllParallel(op)) {
    // iter types 4 is for normall generic op which has batch, channel, h, w. But remember that,
    // there has a pass will eliminatate batch=1 tensor, so size()==4 actually for batch!=1.
    // However, I will not make batch level parallel, due to this kind of full parallels op is
    // element-wise, iterate through all batch is ok and has no performance drop.
    //
    // In brief, I will just tile the innor most parallel, because every element will just be
    // visited only once, the vector size is set to 8 for AVX2.
    if (iterTypes.size() == 4) { ret.tileSizes.push_back({1, 1, 1, 8}); }
    // same as size() for 3, 2, 1
    if (iterTypes.size() == 3) { ret.tileSizes.push_back({1, 1, 8}); }
    if (iterTypes.size() == 2) { ret.tileSizes.push_back({1, 8}); }
    if (iterTypes.size() == 1) { ret.tileSizes.push_back({8}); }

    // all loops can be made parallel
    ret.canForall = SmallVector<bool>(iterTypes.size(), true);

    return ret;
  }

  // case 2. Has reduction and reduction is all behind parallel
  auto _isReductionAtEnd = isOneReductionAtLast(op);
  auto [_isAllParallelBeforeReduction, _pos] = isAllParallelBeforeReduction(op);
  if (!_isAllParallelBeforeReduction) {
    // all loops can't be parallized
    ret.canForall = SmallVector<bool>(iterTypes.size(), false);
    return ret;
  }

  // reduction is tiled with length = 8 too!
  if (_isReductionAtEnd) {
    if (iterTypes.size() == 1) {
      ret.tileSizes.push_back({8});
      ret.canForall = {false};
    } else if (iterTypes.size() == 2) {
      ret.tileSizes.push_back({8, 8});
      ret.canForall = {true, false};
    } else if (iterTypes.size() == 3) {
      ret.tileSizes.push_back({1, 8, 8});
      ret.canForall = {true, true, false};
    } else if (iterTypes.size() == 4) {
      ret.tileSizes.push_back({1, 1, 8, 8});
      ret.canForall = {true, true, true, false};
    }

    return ret;
  }

  if (_isAllParallelBeforeReduction) {
    printf("[ Erro ] The Multi Reduction op is not supportted yet\n");
    std::exit(-1);
  }

  return ret;
}

AdvTileOptions getConv2dInterfaceTileOptions(mlir::Operation* op) {
  // A method enum all sizes for selecting a output batch size.
  auto mathedOutputBatchSize = [](int64_t a) -> int64_t {
    std::vector<int64_t> candidates = {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
    int64_t ret = 1;
    for (auto item : candidates) {
      if (item < a && a % item == 0) {
        ret = item;
        break;
      }
    }
    return ret;
  };

  // judge if one of those input is dynamic sizes;
  auto isDynamic = [](const std::vector<int64_t>& shape) -> bool {
    for (auto item : shape) {
      if (item < 0) return true;
    }
    return false;
  };

  AdvTileOptions res;

  // tile for conv2d with nchw fchw data format
  if (mlir::isa<mlir::linalg::Conv2DNchwFchwOp>(op)) {
    auto input = op->getOperand(0);
    auto filter = op->getOperand(1);
    auto output = op->getOperand(2);

    auto inputShape = mlir::cast<mlir::TensorType>(input.getType()).getShape();
    auto filterShape = mlir::cast<mlir::TensorType>(filter.getType()).getShape();
    auto outputShape = mlir::cast<mlir::TensorType>(output.getType()).getShape();

    int64_t N = inputShape[0];
    int64_t outC = outputShape[1];
    int64_t outH = outputShape[2];
    int64_t outW = outputShape[3];
    int64_t inC = inputShape[1];  // Also F
    int64_t kernelH = filterShape[2];
    int64_t kernelW = filterShape[3];

    if (isDynamic({N, outC, outH, outW, inC, kernelH, kernelW})) { return res; }

    // calculate tile sizes
    // !!! Start solving tiling size. Using some built in logic.
    // For example:
    // %7 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> :
    // vector<2xi64>} ins(%3, %4 : tensor<1x128x30x30xf32>, tensor<128x128x3x3xf32>) outs(%6 :
    // tensor<1x128x28x28xf32>) -> tensor<1x128x28x28xf32>
    //
    // the inputs shape is <1x128x30x30>
    // the kernel shape is <128x128x3x3>
    // the output shape is <1x128x28x28>
    //
    // The recommend tiling size is:
    // 1. [0, 64, 28, 4, 0, 0, 0]
    // 2. [1, 4, 1, 4, 0, 0, 0]
    // 3. [0, 0, 0, 0, 8, 1, 1]
    // 4. [0, 0, 0, 0, 0, 0, 0] (remain)
    SmallVector<int64_t> loops = {N, outC, outH, outW, inC, kernelH, kernelW};
    auto loopsNum = loops.size();

    // solve first level tiling
    {
      res.tileSizes.push_back(SmallVector<int64_t>(loopsNum, 0));
      res.tileSizes[0][1] = mathedOutputBatchSize(outC);
      res.tileSizes[0][2] = outH;
      res.tileSizes[0][3] = 8;
    }

    // solve second level tiling
    { res.tileSizes.push_back({1, 8, 1, 8, 0, 0, 0}); }

    // solve third level tiling
    { res.tileSizes.push_back({0, 0, 0, 0, 8, 1, 1}); }

    // Significant: To make data continuous
    // check the stride is 1 or not. If stride is not 1, tile oh,ow to 1.
    auto convop = mlir::cast<mlir::linalg::Conv2DNchwFchwOp>(op);
    auto stride = convop.getStrides();
    bool strideFlag = false;
    for (auto stride_s : stride) {
      if (!stride_s.isOne()) strideFlag = true;
    }
    if (strideFlag) { res.tileSizes.push_back({0, 0, 1, 1, 0, 0, 0}); }

    return res;
  }
  // tile for conv2d with nchw data format
  if (mlir::isa<mlir::linalg::PoolingNchwMaxOp, mlir::linalg::PoolingNchwSumOp>(op)) {
    auto input = op->getOperand(0);
    auto filter = op->getOperand(1);
    auto output = op->getOperand(2);

    auto inputShape = mlir::cast<mlir::TensorType>(input.getType()).getShape();
    auto filterShape = mlir::cast<mlir::TensorType>(filter.getType()).getShape();
    auto outputShape = mlir::cast<mlir::TensorType>(output.getType()).getShape();

    int64_t N = inputShape[0];
    int64_t outC = outputShape[1];
    int64_t outH = outputShape[2];
    int64_t outW = outputShape[3];
    int64_t kernelH = filterShape[0];
    int64_t kernelW = filterShape[1];

    if (isDynamic({N, outC, outH, outW, kernelH, kernelW})) { return res; }

    // !!! Start solving tiling size. Using some built in logic.
    // For example:
    // %3 = linalg.pooling_nchw_max {dilations = dense<1> : vector<2xi64>, strides = dense<2> :
    // vector<2xi64>} ins(%arg0, %2 : tensor<1x64x114x114xf32>, tensor<3x3xf32>) outs(%1 :
    // tensor<1x64x56x56xf32>) -> tensor<1x64x56x56xf32>
    //
    // the inputs shape is <1x64x114x114>
    // the kernel shape is <3x3>
    // the output shape is <1x64x56x56>
    //
    // The recommend tiling size is:
    // 1. [0, 32, 56, 8, 0, 0]
    // 2. [1, 8, 1, 8, 0, 0]
    // 3. [0, 0, 0, 0, 1, 3]
    // 4. [0, 0, 0, 0, 0, 0] (remain)
    SmallVector<int64_t> loops = {N, outC, outH, outW, kernelH, kernelW};
    auto loopsNum = loops.size();

    // solve first level tiling
    {
      res.tileSizes.push_back(SmallVector<int64_t>(loopsNum, 0));
      res.tileSizes[0][1] = mathedOutputBatchSize(outC);
      res.tileSizes[0][2] = outH;
      res.tileSizes[0][3] = 8;
    }

    // solve second level tiling
    { res.tileSizes.push_back(SmallVector<int64_t>{1, 8, 1, 8, 0, 0}); }

    // solve third level tiling
    { res.tileSizes.push_back(SmallVector<int64_t>{0, 0, 0, 0, 1, kernelW}); }

    // Significant: To make data continuous
    // check the stride is 1 or not. If stride is not 1, tile oh,ow to 1.
    if (mlir::isa<mlir::linalg::PoolingNchwMaxOp>(op)) {
      auto convop = mlir::cast<mlir::linalg::PoolingNchwMaxOp>(op);
      auto stride = convop.getStrides();
      bool strideFlag = false;
      for (auto stride_s : stride) {
        if (!stride_s.isOne()) strideFlag = true;
      }
      if (strideFlag) { res.tileSizes.push_back({0, 0, 1, 1, 0, 0}); }
    } else if (mlir::isa<mlir::linalg::PoolingNchwSumOp>(op)) {
      auto convop = mlir::cast<mlir::linalg::PoolingNchwSumOp>(op);
      auto stride = convop.getStrides();
      bool strideFlag = false;
      for (auto stride_s : stride) {
        if (!stride_s.isOne()) strideFlag = true;
      }
      if (strideFlag) { res.tileSizes.push_back({0, 0, 1, 1, 0, 0}); }
    }
  }

  return res;
}

// AVX2, Vector size = 8. Static. But set Matmul Vec=4
AdvTileOptions getMatMulTileOptions(mlir::Operation* op) {
  AdvTileOptions ret;
  ret.tileSizes.push_back({16, 16, 0});
  ret.tileSizes.push_back({8, 8, 0});
  ret.tileSizes.push_back({0, 0, 8});
  ret.canForall = {true, true, false};
  return ret;
}

bool tileGenericUseScfFor(IRRewriter& rewriter, mlir::Operation* op) {
  auto opt = getGenericTileOptions(op);

  assert(opt.tileSizes[0].size() == opt.canForall.size());

  mlir::scf::SCFTilingOptions scfOptions;
  SmallVector<mlir::OpFoldResult> sizes;
  for (size_t kk = 0; kk < opt.tileSizes[0].size(); ++kk) {
    sizes.push_back(rewriter.getIndexAttr(opt.tileSizes[0][kk]));
  }
  scfOptions.setTileSizes(sizes);
  auto tileInterface = mlir::dyn_cast<mlir::TilingInterface>(op);

  // tile
  auto result = mlir::scf::tileUsingSCFForOp(rewriter, tileInterface, scfOptions);
  if (failed(result)) {
    return false;
  } else {
    // tag each for loops with can be parallel tag.
    assert(opt.canForall.size() == result->loops.size());
    for (size_t i = 0; i < opt.canForall.size(); ++i) {
      auto _forOp = mlir::cast<mlir::scf::ForOp>(result->loops[i]);
      _forOp->setAttr("parallel", rewriter.getBoolAttr(opt.canForall[i]));
    }
  }
  rewriter.replaceOp(op, result->replacements);

  return true;
}

// Conv2d tile is seperated to pool and conv2d, and will invlove decompose method. But remember that
// the decompose method is just another pass, this tiling method is just for tiling. I will try
// multiple tiling sizes for output batch size(because output batch sizes is normally set to 16,
// 32, 64...)
bool tileConv2dInterfaceUseScfFor(IRRewriter& rewriter, mlir::Operation* op) {
  auto moptions = getConv2dInterfaceTileOptions(op);
  auto curOp = op;
  for (size_t i = 0; i < moptions.tileSizes.size(); ++i) {
    mlir::scf::SCFTilingOptions options;
    SmallVector<mlir::OpFoldResult> sizes;
    for (size_t kk = 0; kk < moptions.tileSizes[i].size(); ++kk) {
      sizes.push_back(rewriter.getIndexAttr(moptions.tileSizes[i][kk]));
    }
    options.setTileSizes(sizes);
    auto tileInterface = mlir::dyn_cast<mlir::TilingInterface>(curOp);
    auto result = mlir::scf::tileUsingSCFForOp(rewriter, tileInterface, options);
    if (failed(result)) return false;
    rewriter.replaceOp(curOp, result.value().replacements);
    curOp = result.value().tiledOps[0];
  }
  return true;
}

// MatMul tiling
bool tileMatMulUseScfFor(IRRewriter& rewriter, mlir::Operation* op) {
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

    // tile
    rewriter.setInsertionPoint(curOp);
    auto result = mlir::scf::tileUsingSCFForOp(rewriter, tileInterface, options);
    if (failed(result)) {
      return false;
    } else {
      for (auto opptr : result->loops) {
        auto _opptr = mlir::cast<mlir::scf::ForOp>(opptr);
        _opptr->setAttr("parallel", rewriter.getBoolAttr(moptions.canForall[i]));
      }
    }
    rewriter.replaceOp(curOp, result->replacements);
    curOp = result->tiledOps[0];
  }
  return true;
}

void emitTileFailedError(bool isOk, mlir::Operation* op) {
  if (!isOk) {
    printf("[ Warn ] When tiling %s op, optimization failed.\n",
           op->getName().getStringRef().str().c_str());
  }
}

class AdvancedTileAndDispatchPass final
    : public impl::AdvancedTileAndDispatchBase<AdvancedTileAndDispatchPass> {
  void runOnOperation() override {
    IRRewriter rewriter(&getContext());
    SmallVector<mlir::Operation*> matMulCandidates;
    SmallVector<mlir::Operation*> conv2dInterfaceCandidates;
    SmallVector<mlir::Operation*> genericCandidates;
    getOperation().walk([&](mlir::linalg::LinalgOp op) {
      if (mlir::isa<mlir::linalg::MatmulOp>(op)) {
        matMulCandidates.push_back(op);
        return;
      }
      if (mlir::isa<mlir::linalg::Conv2DNchwFchwOp, mlir::linalg::PoolingNchwMaxOp,
                    mlir::linalg::PoolingNchwSumOp>(op)) {
        conv2dInterfaceCandidates.push_back(op);
        return;
      }
      if (mlir::isa<mlir::linalg::GenericOp>(op)) {
        genericCandidates.push_back(op);
        return;
      }
    });

    for (auto op : matMulCandidates) { emitTileFailedError(tileMatMulUseScfFor(rewriter, op), op); }
    for (auto op : conv2dInterfaceCandidates) {
      emitTileFailedError(tileConv2dInterfaceUseScfFor(rewriter, op), op);
    }
    for (auto op : genericCandidates) {
      emitTileFailedError(tileGenericUseScfFor(rewriter, op), op);
    }
  }
};

}  // namespace

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createAdvancedTileAndDispatchPass() {
  return std::make_unique<AdvancedTileAndDispatchPass>();
}

}  // namespace mlir::nncv