#ifndef NNCV_BASE_HPP_
#define NNCV_BASE_HPP_

/**
 * Error checker.
 * Macro: Checker, Loger
 * Class: Expect, error, Maybe
 */
// maybe class is reference from oneflow, https://zhuanlan.zhihu.com/p/423811115

/**
 * Load from cmake. The basic settings of nncv
 * Including the hardware setting.
 * And some image pre-processing backend settings.
 */
namespace nncv {

#ifdef NNCV_ENABLE_CUDA
static const bool is_cuda_available = true;
#else
static const bool is_cuda_available = false;
#endif

enum SimdArch : int {
  SSE2 = 0,
  AVX2,
  AVX512,
};

#ifdef NNCV_HAVE_SSE
static const bool is_simd_sse_available = true;
#if not defined(NNCV_HAVE_AVX2) and not defined(NNCV_HAVE_AVX512)
static const SimdArch simd_backend = SimdArch::SSE2;
#endif
#else
static const bool is_simd_avx2_available = false;
#endif

#ifdef NNCV_HAVE_AVX2
static const bool is_simd_avx2_available = true;
#if not defined(NNCV_HAVE_AVX512)
static const SimdArch simd_backend = SimdArch::AVX2;
#endif
#else
static const bool is_simd_avx2_available = false;
#endif

#ifdef NNCV_HAVE_AVX512
static const bool is_simd_avx512_available = true;
static const SimdArch simd_backend = SimdArch::AVX512;
#else
static const bool is_simd_avx512_available = false;
#endif

}  // namespace nncv

#endif  //! NNCV_BASE_HPP_