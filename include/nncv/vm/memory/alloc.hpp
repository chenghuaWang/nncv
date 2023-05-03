#ifndef NNCV_ALLOC_HPP
#define NNCV_ALLOC_HPP

#include "nncv/core/base.hpp"
#include "nncv/core/common/device.hpp"

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

namespace nncv {
namespace vm {

struct GlobalMemRegisterTable {};

class MemPool {};

class MemPoolHost final : public MemPool {};

class MemPoolCuda final : public MemPool {};
}  // namespace vm
}  // namespace nncv

#endif