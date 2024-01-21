/**
 * @file MatMulOptParallelVec.cpp
 * @author chenghua.wang (chenghua.wang.edu@gmail.com)
 * @brief MatMul optimization for x86 CPU with AVX/SSE
 * @version 0.1
 * @date 2024-01-21
 *
 * @copyright Copyright (c) 2024
 *
 * Algorithms used here:
 *
 */
#include "nncv/compiler/Conversion/MatMulOptimize/MatMulOptParallelVec.hpp"
#include "nncv/compiler/Utils/PlatformCtx.hpp"

#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
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
#include "mlir/IR/IntegerSet.h"

namespace mlir::nncv {
#define GEN_PASS_DEF_MATMULOPTIMIZATION_PARALLELVEC
#include "Conversion/Passes.h.inc"
}  // namespace mlir::nncv

namespace mlir {
namespace nncv {
namespace matmul_optimize {

namespace {}  // namespace

std::unique_ptr<mlir::Pass> createMatMulOptimizationParallelVecPass() {}
}  // namespace matmul_optimize
}  // namespace nncv
}  // namespace mlir