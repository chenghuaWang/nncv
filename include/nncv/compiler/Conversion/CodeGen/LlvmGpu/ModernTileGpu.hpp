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
#ifndef NNCV_C_CODEGEN_MODERN_TILE_GPU_HPP_
#define NNCV_C_CODEGEN_MODERN_TILE_GPU_HPP_

#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Transforms/DialectConversion.h"

#define GEN_PASS_DECL_MODERNTILEGPU
#include "Conversion/Passes.h.inc"

namespace mlir::nncv {

namespace {}

std::unique_ptr<InterfacePass<mlir::FunctionOpInterface>> createModernOneShotTileAllGpuPass();

}  // namespace mlir::nncv

#endif  //! NNCV_C_CODEGEN_MODERN_TILE_GPU_HPP_