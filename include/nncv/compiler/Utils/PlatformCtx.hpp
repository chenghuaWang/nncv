/**
 * @file PlatformCtx.hpp
 * @author chenghua.wang (chenghua.wang.edu@gmail.com)
 * @brief A head file load all Platform based Ctx.
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <string>
#include <vector>
#include <cpuinfo/include/cpuinfo.h>

#ifdef NNCV_ENABLE_CUDA
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#endif

namespace nncv {
namespace compiler {
namespace utils {

struct MatMulTileSize_CPU {
  std::vector<int64_t> outerLevelLoops = {8, 32, 0};
  std::vector<int64_t> innerLevelLoops = {4, 4, 0};
  std::vector<int64_t> registerLevelLoops = {0, 0, 4};
};

struct MatMulVec_CPU {
  std::vector<int64_t> vecSize = {4, 4, 4};
};

struct LinalgGenericTileSize_CPU {
  std::vector<int64_t> outerLevelLoops = {8, 32, 0};
  std::vector<int64_t> innerLevelLoops = {4, 4, 0};
  std::vector<int64_t> registerLevelLoops = {0, 0, 4};
};

struct LinalgGenericVec_CPU {
  std::vector<int64_t> vecSize = {0, 4, 4, 4};
};

// now support X86 and NVIDIA, general-linux, with only single CPU/GPU
struct PlatformCtx {
  /// Basic CPU Info
  std::string CpuName;
  size_t CpuL1CacheSize;
  size_t CpuL2CacheSize;
  size_t CpuL3CacheSize;

  /// Basic GPU Info
  std::string GpuName;
  size_t GpuTotalMemory;
  size_t GpuTotalConstMem;
  size_t GpuSharedMemPerBlock;

  /// x86 CPU Based Vector Instruction. 2D Vector is not support yet.
#if NNCV_HAVE_SSE == 1
  size_t CpuHasSSE = 1;
#else
  size_t CpuHasSSE = 0;
#endif  //! NNCV_HAVE_SSE == 1
#if NNCV_HAVE_AVX2 == 1
  size_t CpuHasAVX2 = 1;
#else
  size_t CpuHasAVX2 = 0;
#endif  //! NNCV_HAVE_AVX2 == 1

  /// tileSize, SplitingSize, and so on.
  size_t* CB_TileSize = nullptr;
  size_t CB_SplitSize;

  /// Mat Mul on CPU
  int64_t MatMul_VecSize;
  int64_t MatMul_Kernel_M = 4;
  int64_t MatMul_Kernel_N = 4;

  /// MatMul Pass's Tiled Size
  MatMulTileSize_CPU MatMulTileCpu;
  MatMulVec_CPU MatMulVecCpu;
  /// Linalg generic tile size
  LinalgGenericTileSize_CPU LinalgGenericTileCpu;
  LinalgGenericVec_CPU LinalgGenericVecCpu;

  inline void init() {
    //< conv optimize
    if (CpuHasAVX2) CB_SplitSize = 8;  // 256bit / 32bit
    if (!CpuHasAVX2 && CpuHasSSE) CB_SplitSize = 4;

    //< mat mul optimization
    if (CpuHasAVX2) MatMul_VecSize = 8;  // 256bit / 32bit
    if (!CpuHasAVX2 && CpuHasSSE) MatMul_VecSize = 4;
  }

  PlatformCtx() = default;
  ~PlatformCtx() {}
  PlatformCtx(const PlatformCtx&) = delete;
  PlatformCtx& operator=(const PlatformCtx&) = delete;

  static PlatformCtx& getInstance() {
    static PlatformCtx instance;
    return instance;
  }

  void InitFromConfigFile();
};

inline static void PlatformCtxInit(bool printed = false) {
  if (printed) printf("[ INFO ] Detecting Platform.\n");
  cpuinfo_initialize();

  PlatformCtx ctx{};
  ctx.CpuName = cpuinfo_get_package(0)->name;
  ctx.CpuL1CacheSize = cpuinfo_get_processor(0)->cache.l1d->size;
  ctx.CpuL2CacheSize = cpuinfo_get_processor(0)->cache.l2->size;
  ctx.CpuL3CacheSize = cpuinfo_get_processor(0)->cache.l3->size;
  if (printed) {
    printf("[ INFO ] Running on %s CPU, L1: %zuKB, L2: %zuKB, L3: %zuMB\n", ctx.CpuName.c_str(),
           ctx.CpuL1CacheSize >> 10, ctx.CpuL2CacheSize >> 10, ctx.CpuL3CacheSize >> 20);
  }

#ifdef NNCV_ENABLE_CUDA
  int GpuDeviceCount;
  cudaGetDeviceCount(&GpuDeviceCount);
  if (GpuDeviceCount != 1) {
    printf("[ WARN ] GPU Count is: %d, only support (cpu or single card)\n", GpuDeviceCount);
  }
  cudaDeviceProp DeviceProp;
  cudaGetDeviceProperties(&DeviceProp, 0);
  ctx.GpuName = DeviceProp.name;
  ctx.GpuTotalMemory = DeviceProp.totalGlobalMem;
  ctx.GpuSharedMemPerBlock = DeviceProp.sharedMemPerBlock;
  ctx.GpuTotalConstMem = DeviceProp.totalConstMem;
  if (printed) {
    printf("[ INFO ] Has GPU %s, TotalMem: %fGB, SharedMem(perBlock): %fKB, TotalConstMem: %fKB\n",
           ctx.GpuName.c_str(), (float)ctx.GpuTotalMemory / (float)(1 << 30),
           (float)ctx.GpuSharedMemPerBlock / (float)(1 << 10),
           (float)ctx.GpuTotalConstMem / (float)(1 << 10));
  }

#endif
  if (printed) { printf("[ INFO ] Done.\n"); }
}

}  // namespace utils
}  // namespace compiler

}  // namespace nncv