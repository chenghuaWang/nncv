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
#include <string>
#include <cpuinfo/include/cpuinfo.h>

#ifdef NNCV_ENABLE_CUDA
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#endif

namespace nncv {
namespace compiler {
namespace utils {

// now support X86 and NVIDIA, general-linux, with only single CPU/GPU
struct PlatformCtx {
  std::string CpuName;
  size_t CpuL1CacheSize;
  size_t CpuL2CacheSize;
  size_t CpuL3CacheSize;
  std::string GpuName;
  size_t GpuTotalMemory;
  size_t GpuTotalConstMem;
  size_t GpuSharedMemPerBlock;
  // TODOMaximum size of each dimension of a block
};

inline static PlatformCtx PlatformCtxInit() {
  printf("[ INFO ] Detecting Platform.\n");
  cpuinfo_initialize();

  PlatformCtx ctx{};
  ctx.CpuName = cpuinfo_get_package(0)->name;
  ctx.CpuL1CacheSize = cpuinfo_get_processor(0)->cache.l1d->size;
  ctx.CpuL2CacheSize = cpuinfo_get_processor(0)->cache.l2->size;
  ctx.CpuL3CacheSize = cpuinfo_get_processor(0)->cache.l3->size;

  printf("[ INFO ] Running on %s CPU, L1: %zuKB, L2: %zuKB, L3: %zuMB\n", ctx.CpuName.c_str(),
         ctx.CpuL1CacheSize >> 10, ctx.CpuL2CacheSize >> 10, ctx.CpuL3CacheSize >> 20);

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
  printf("[ INFO ] Has GPU %s, TotalMem: %fGB, SharedMem(perBlock): %fKB, TotalConstMem: %fKB\n",
         ctx.GpuName.c_str(), (float)ctx.GpuTotalMemory / (float)(1 << 30),
         (float)ctx.GpuSharedMemPerBlock / (float)(1 << 10),
         (float)ctx.GpuTotalConstMem / (float)(1 << 10));
#endif
  printf("[ INFO ] Done.\n");
  return ctx;
}

}  // namespace utils
}  // namespace compiler

}  // namespace nncv