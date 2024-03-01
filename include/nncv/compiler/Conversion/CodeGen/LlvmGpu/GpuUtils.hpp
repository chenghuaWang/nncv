// MLIR has no raw c++ methods for map block. So I impl a similar method here.
#ifndef NNCV_C_CODEGEN_GPU_UTILS_HPP_
#define NNCV_C_CODEGEN_GPU_UTILS_HPP_

#include <cstdint>
#include <optional>
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
#include "mlir/IR/Location.h"
#include "mlir/IR/PatternMatch.h"

namespace mlir::nncv::codegen_llvm_gpu {
bool checkGpuLimits(std::optional<int64_t> gridDimX, std::optional<int64_t> gridDimY,
                    std::optional<int64_t> gridDimZ, std::optional<int64_t> blockDimX,
                    std::optional<int64_t> blockDimY, std::optional<int64_t> blockDimZ);

bool createGpuLaunch(mlir::RewriterBase& rewriter, mlir::Location loc,
                     mlir::gpu::LaunchOp& launchOp, std::optional<int64_t> gridDimX = std::nullopt,
                     std::optional<int64_t> gridDimY = std::nullopt,
                     std::optional<int64_t> gridDimZ = std::nullopt,
                     std::optional<int64_t> blockDimX = std::nullopt,
                     std::optional<int64_t> blockDimY = std::nullopt,
                     std::optional<int64_t> blockDimZ = std::nullopt);

bool alterGpuLaunch(RewriterBase& rewriter, gpu::LaunchOp gpuLaunch,
                    std::optional<int64_t> gridDimX = std::nullopt,
                    std::optional<int64_t> gridDimY = std::nullopt,
                    std::optional<int64_t> gridDimZ = std::nullopt,
                    std::optional<int64_t> blockDimX = std::nullopt,
                    std::optional<int64_t> blockDimY = std::nullopt,
                    std::optional<int64_t> blockDimZ = std::nullopt);
}  // namespace mlir::nncv::codegen_llvm_gpu

#endif  //! NNCV_C_CODEGEN_GPU_UTILS_HPP_