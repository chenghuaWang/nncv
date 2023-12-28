#ifndef NNCV_ALLOC_HPP
#define NNCV_ALLOC_HPP

#if defined(_WIN32)
#include <corecrt_malloc.h>
#elif defined(__unix__)
#include <stdlib.h>
#else
#include <memory.h>
#endif

#include "nncv/core/base.hpp"
#include "nncv/core/common/device.hpp"

#ifdef NNCV_ENABLE_CUDA
#include "nncv/vm/cuda/vm_alloc_cuda.cuh"
#endif

#pragma once

/*!
 *@brief    To align data.
 *@details  x normally set to 4, 8, 16. This attribute will make
 * data aligned to x.
 * For example, you can use this macro like this:
 * float foo_1[10] NNCV_ALIGNED(4);
 * int32_t foo_2[10] NNCV_ALIGNED(8);
 */
#define NNCV_ALIGNED(x) __attribute__((aligned(x)))
#define NNCV_ALIGNED_4 NNCV_ALIGNED(4)
#define NNCV_ALIGNED_8 NNCV_ALIGNED(8)
#define NNCV_ALIGNED_16 NNCV_ALIGNED(16)
#define NNCV_ALIGNED_32 NNCV_ALIGNED(32)
#define NNCV_ALIGNED_64 NNCV_ALIGNED(64)

/**
 * @brief AVX 256 aligned to 32 * 8 bits
 * AVX 512 aligned to 64 * 8 bits
 * SSE 128 aligned to 16 * 8 bits
 */
#if defined(NNCV_HAVE_AVX512)
#define NNCV_ALLOC_ALIGNED_BITS 64
#elif defined(NNCV_HAVE_AVX2)
#define NNCV_ALLOC_ALIGNED_BITS 32
#elif defined(NNCV_HAVE_SSE)
#define NNCV_ALLOC_ALIGNED_BITS 16
#endif

#define NNCV_ALLOC_SAFEGUARD 0

namespace nncv {
namespace vm {

/**
 * @brief Aligns a pointer to the specified number of bytes
 *
 * @tparam _Tp
 * @param ptr
 * @param n Alignment size that must be a power of two
 * @return _Tp*
 * @ref https://github.com/Tencent/ncnn/blob/master/src/allocator.h
 */
template<typename _Tp>
NNCV_FORCE_INLINE _Tp* AlignPtr(_Tp* ptr, int n = (int)sizeof(_Tp)) {
  return (_Tp*)(((size_t)ptr + n - 1) & -n);
}

/**
 * @brief Only for Debug purpose / Temp value alloc. The Stream mechanism will alloc memory in
 * memory pool instead of using raw alloc function.
 *
 * For Host: Why udata: https://zhuanlan.zhihu.com/p/335774042, this trick is also used in OpenCV
 * and MNN
 *
 * For CUDA device: Any address of a variable residing in global memory or returned by one of the
 * memory allocation routines from the driver or runtime API is always aligned to at least 256
 * bytes.
 *
 * @param _size
 * @return void*
 */
NNCV_FORCE_INLINE static void* MemAlloc(size_t _size, const Device& _device) {
  switch (_device.Type) {
    case kHost:
#if defined(_MSC_VER)
    {
      return _aligned_malloc(_size, NNCV_ALLOC_ALIGNED_BITS);
    }
#elif defined(__unix__) && _POSIX_C_SOURCE >= 200112L
    {
      void* ptr = nullptr;
      if (posix_memalign(&ptr, NNCV_ALLOC_ALIGNED_BITS, _size + NNCV_ALLOC_SAFEGUARD))
        ptr = nullptr;
      return ptr;
    }
#else
    {
      unsigned char* udata = (unsigned char*)malloc(_size + sizeof(void*) + NNCV_ALLOC_ALIGNED_BITS
                                                    + NNCV_ALLOC_SAFEGUARD);
      if (!udata) return nullptr;
      unsigned char** _data = AlignPtr((unsigned char**)udata + 1, NNCV_ALLOC_ALIGNED_BITS);
      _data[-1] = udata;
      return _data;
    }
#endif
    case kCuda: {
      void* ptr = nullptr;
      _VmCudaMallocWarper(&ptr, _size);
      break;
    }
    case kSelfDefined: break;
  }
  return nullptr;
}

NNCV_FORCE_INLINE static void MemFree(void* _ptr, const Device& _device) {
  switch (_device.Type) {
    case kHost:
#if defined(_MSC_VER)
    {
      if (_ptr) {
        _aligned_free(_ptr);
        return;
      }
    }
#elif defined(__unix__) && _POSIX_C_SOURCE >= 200112L
    {
      free(_ptr);
      return;
    }
#else
    {
      unsigned char* udata = ((unsigned char**)ptr)[-1];
      free(udata);
    }
#endif
    case kCuda: {
      _VmCudaFreeWarper(_ptr);
    }
    case kSelfDefined: break;
  }
}

struct GlobalMemRegisterTable {};

class MemPool {
 public:
  virtual void* Alloc() { return nullptr; };
  virtual void Free(){};

  virtual void __Raw(){};

 private:
};

class MemPoolHost final : public MemPool {
 public:
  void* Alloc() override;
  void Free() override;

  void __Raw() override;

 private:
};

class MemPoolCuda final : public MemPool {
 public:
  void* Alloc() override;
  void Free() override;

  void __Raw() override;

 private:
};
}  // namespace vm
}  // namespace nncv

#endif