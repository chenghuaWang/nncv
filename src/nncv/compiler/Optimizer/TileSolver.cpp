#include "nncv/compiler/Optimizer/TileSolver.hpp"
#include "mlir/Dialect/Linalg/IR/Linalg.h"
#include "mlir/Dialect/Linalg/IR/LinalgInterfaces.h"
#include "mlir/IR/BuiltinTypes.h"

namespace nncv::compiler {
namespace optimizer {

void TileSolver::registerOp(const std::string& opsName, mlir::Operation* op) {
  auto tmp = TileOpsNode(opsName, op);
  tmp.setUUID(m_UUID++);
  auto options = TileOptions();
  m_Dict[tmp] = options;
  __m_link_to_dict[op] = tmp;
}

void TileSolver::solveTileSize() {
  for (auto& node : m_Dict) {
    auto _op = mlir::cast<mlir::linalg::LinalgOp>(node.first.getOp());

    if (mlir::isa<mlir::linalg::MatmulOp>(_op)) {
      TILE_SOLVER_SET_SOLVED_SIZES(_op, solveTileSizesMatMul)
      continue;
    }

    if (mlir::isa<mlir::linalg::PoolingNchwMaxOp, mlir::linalg::PoolingNchwSumOp>(_op)) {
      TILE_SOLVER_SET_SOLVED_SIZES(_op, solveTileSizesPooling);
      continue;
    }

    if (mlir::isa<mlir::linalg::Conv2DNchwFchwOp>(_op)) {
      TILE_SOLVER_SET_SOLVED_SIZES(_op, solveTileSizesConv2d);
      continue;
    }

    // generic op should be processed in the latest position.
    if (mlir::isa<mlir::linalg::GenericOp>(_op)) {
      TILE_SOLVER_SET_SOLVED_SIZES(_op, solveTileSizesGeneric);
      continue;
    }

    printf("[ Warn ] %s is not supported in op tile solver, you should figure it out using config "
           "file. In this file will fail through to nested for loops. Waring form TileSolver\n",
           _op->getName().getStringRef().str().c_str());
  }
}

void TileSolver::solveThreadDispatch() {
  for (auto& node : m_Dict) {}
}

TileOptions TileSolver::getRecommendOption(mlir::Operation* op) {}

void TileSolver::dump() {
  for (auto item : m_Dict) { printf("Registered Ops: %s\n", item.first.getUniqueName().c_str()); }
}

std::vector<std::vector<int64_t>> TileSolver::solveTileSizesMatMul(mlir::Operation* op) {
  std::vector<std::vector<int64_t>> res;
  return res;
}

std::vector<std::vector<int64_t>> TileSolver::solveTileSizesPooling(mlir::Operation* op) {
  std::vector<std::vector<int64_t>> res;
  auto _op = mlir::cast<mlir::linalg::LinalgOp>(op);
  if (mlir::isa<mlir::linalg::PoolingNchwMaxOp, mlir::linalg::PoolingNchwSumOp>(_op)) {
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
    std::vector<int64_t> loops = {N, outC, outH, outW, kernelH, kernelW};
    auto loopsNum = loops.size();

    // solve first level tiling
    {
      res.emplace_back(std::vector<int64_t>(loopsNum, 0));
      res[0][1] = get2sPowOrSelf(outC);
      res[0][2] = outH;
      res[0][3] = 8;
    }

    // solve second level tiling
    { res.emplace_back(std::vector<int64_t>{1, 8, 1, 8, 0, 0}); }

    // solve third level tiling
    { res.emplace_back(std::vector<int64_t>{0, 0, 0, 0, 1, kernelW}); }

    // solve fourth level tiling
    { res.emplace_back(std::vector<int64_t>(loopsNum, 0)); }

    return res;
  }

  return res;
}

std::vector<std::vector<int64_t>> TileSolver::solveTileSizesConv2d(mlir::Operation* op) {
  std::vector<std::vector<int64_t>> res;
  auto _op = mlir::cast<mlir::linalg::LinalgOp>(op);
  if (mlir::isa<mlir::linalg::Conv2DNchwFchwOp>(_op)) {
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
    std::vector<int64_t> loops = {N, outC, outH, outW, inC, kernelH, kernelW};
    auto loopsNum = loops.size();

    // solve first level tiling
    {
      res.emplace_back(std::vector<int64_t>(loopsNum, 0));
      res[0][1] = get2sPowOrSelf(outC);
      res[0][2] = outH;
      res[0][3] = 8;
    }

    // solve second level tiling
    { res.emplace_back(std::vector<int64_t>{1, 8, 1, 8, 0, 0, 0}); }

    // solve third level tiling
    { res.emplace_back(std::vector<int64_t>{0, 0, 0, 0, 8, 1, 1}); }

    // solve fourth level tiling
    { res.emplace_back(std::vector<int64_t>(loopsNum, 0)); }

    return res;
  }

  return res;
}

std::vector<std::vector<int64_t>> TileSolver::solveTileSizesGeneric(mlir::Operation* op) {
  std::vector<std::vector<int64_t>> res;
  return res;
}

bool TileSolver::isDynamic(const std::vector<int64_t>& shape) {
  for (auto item : shape) {
    if (item < 0) return true;
  }
  return false;
}

int64_t TileSolver::get2sPowOrSelf(int64_t i) {
  // set candidates
  int64_t candidates[] = {8, 16, 32, 64};

  // try
  if (i < 8) return i;

  int64_t ret = i;
  for (size_t idx = 0; idx < 4; idx++) {
    if (i != candidates[idx] && i > 2 * candidates[idx]) { ret = candidates[idx]; }
  }
  return ret;
}

}  // namespace optimizer
}  // namespace nncv::compiler