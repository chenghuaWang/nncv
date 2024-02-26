#include "nncv/compiler/Conversion/CodeGen/LlvmGpu/GpuUtils.hpp"
#include <cstdio>
#include "mlir/Dialect/Arith/IR/Arith.h"

namespace mlir::nncv::codegen_llvm_gpu {
bool checkGpuLimits(std::optional<int64_t> gridDimX, std::optional<int64_t> gridDimY,
                    std::optional<int64_t> gridDimZ, std::optional<int64_t> blockDimX,
                    std::optional<int64_t> blockDimY, std::optional<int64_t> blockDimZ) {
  // hard code limitation
  static constexpr int maxTotalBlockdim = 1024;
  static constexpr int maxBlockdimx = 1024;
  static constexpr int maxBlockdimy = 1024;
  static constexpr int maxBlockdimz = 64;
  static constexpr int maxTotalGriddim = 2147483647;
  static constexpr int maxGriddimx = 2147483647;
  static constexpr int maxGriddimy = 65535;
  static constexpr int maxGriddimz = 65535;

  if ((blockDimX.value_or(1) * blockDimY.value_or(1) * blockDimZ.value_or(1)) > maxTotalBlockdim
      || (gridDimX.value_or(1) * gridDimY.value_or(1) * gridDimZ.value_or(1)) > maxTotalGriddim
      || blockDimX.value_or(1) > maxBlockdimx || blockDimY.value_or(1) > maxBlockdimy
      || blockDimZ.value_or(1) > maxBlockdimz || gridDimY.value_or(1) > maxGriddimy
      || gridDimZ.value_or(1) > maxGriddimz || gridDimX.value_or(1) > maxGriddimx) {
    printf("[ Erro ] Trying to launch a GPU kernel whose grid_dims is larger than the limits.");
    return false;
  }
  return true;
}

bool createGpuLaunch(mlir::RewriterBase& rewriter, mlir::Location loc,
                     mlir::gpu::LaunchOp& launchOp, std::optional<int64_t> gridDimX,
                     std::optional<int64_t> gridDimY, std::optional<int64_t> gridDimZ,
                     std::optional<int64_t> blockDimX, std::optional<int64_t> blockDimY,
                     std::optional<int64_t> blockDimZ) {
  // check the gpu size's limits
  auto limits = checkGpuLimits(gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ);
  if (!limits) return limits;

  auto createConst = [&](int dim) {
    return rewriter.create<mlir::arith::ConstantIndexOp>(loc, dim);
  };

  OpBuilder::InsertionGuard guard(rewriter);
  Value one = createConst(1);
  Value gridSizeX = gridDimX.has_value() ? createConst(gridDimX.value()) : one;
  Value gridSizeY = gridDimY.has_value() ? createConst(gridDimY.value()) : one;
  Value gridSizeZ = gridDimZ.has_value() ? createConst(gridDimZ.value()) : one;
  Value blkSizeX = blockDimX.has_value() ? createConst(blockDimX.value()) : one;
  Value blkSizeY = blockDimY.has_value() ? createConst(blockDimY.value()) : one;
  Value blkSizeZ = blockDimZ.has_value() ? createConst(blockDimZ.value()) : one;
  launchOp = rewriter.create<mlir::gpu::LaunchOp>(loc, gridSizeX, gridSizeY, gridSizeZ, blkSizeX,
                                                  blkSizeY, blkSizeZ);
  rewriter.setInsertionPointToEnd(&launchOp.getBody().front());
  rewriter.create<mlir::gpu::TerminatorOp>(loc);

  return true;
}

bool alterGpuLaunch(RewriterBase& rewriter, gpu::LaunchOp gpuLaunch,
                    std::optional<int64_t> gridDimX, std::optional<int64_t> gridDimY,
                    std::optional<int64_t> gridDimZ, std::optional<int64_t> blockDimX,
                    std::optional<int64_t> blockDimY, std::optional<int64_t> blockDimZ) {
  // check the gpu size's limits
  auto limits = checkGpuLimits(gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ);
  if (!limits) return limits;

  gpu::KernelDim3 currentBlockdim = gpuLaunch.getBlockSizeOperandValues();
  OpBuilder::InsertionGuard guard(rewriter);
  rewriter.setInsertionPointAfterValue(currentBlockdim.x);
  auto createConstValue = [&](int dim) {
    return rewriter.create<arith::ConstantIndexOp>(currentBlockdim.x.getLoc(), dim);
  };

  if (gridDimX.has_value()) {
    gpuLaunch.getGridSizeXMutable().assign(createConstValue(gridDimX.value()));
  }
  if (gridDimY.has_value()) {
    gpuLaunch.getGridSizeYMutable().assign(createConstValue(gridDimY.value()));
  }
  if (gridDimZ.has_value()) {
    gpuLaunch.getGridSizeZMutable().assign(createConstValue(gridDimZ.value()));
  }
  if (blockDimX.has_value()) {
    gpuLaunch.getBlockSizeXMutable().assign(createConstValue(blockDimX.value()));
  }
  if (blockDimY.has_value()) {
    gpuLaunch.getBlockSizeYMutable().assign(createConstValue(blockDimY.value()));
  }
  if (blockDimZ.has_value()) {
    gpuLaunch.getBlockSizeZMutable().assign(createConstValue(blockDimZ.value()));
  }

  return true;
}

}  // namespace mlir::nncv::codegen_llvm_gpu