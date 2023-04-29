#ifndef NNCV_BASE_HPP_
#define NNCV_BASE_HPP_

#include <cstdio>
#include <cstdlib>

#define EXIT_CUDA_ERROR 1

#define WIN32_EXPORTS true

#ifdef WIN32
#ifdef WIN32_EXPORTS
#define EXPORT_DLL __declspec(dllexport)
#else
#define IMPORT_DLL __declspec(dllimport)
#endif
#endif

/**
 * Load from cmake. The basic settings of nncv
 * Including the hardware setting.
 * And some image pre-processing backend settings.
 */
namespace nncv {

#ifdef NNCV_ENABLE_CUDA
static const bool is_cuda_builtin = true;
#else
static const bool is_cuda_builtin = false;
#endif

enum SimdArch : int {
  SSE2 = 0,
  AVX2,
  AVX512,
};

#ifdef NNCV_HAVE_SSE
static const bool is_simd_sse_builtin = true;
#if !defined(NNCV_HAVE_AVX2) && !defined(NNCV_HAVE_AVX512)
static const SimdArch simd_backend = SimdArch::SSE2;
#endif
#else
static const bool is_simd_avx2_builtin = false;
#endif

#ifdef NNCV_HAVE_AVX2
static const bool is_simd_avx2_builtin = true;
#if !defined(NNCV_HAVE_AVX512)
static const SimdArch simd_backend = SimdArch::AVX2;
#endif
#else
static const bool is_simd_avx2_builtin = false;
#endif

#ifdef NNCV_HAVE_AVX512
static const bool is_simd_avx512_builtin = true;
static const SimdArch simd_backend = SimdArch::AVX512;
#else
static const bool is_simd_avx512_builtin = false;
#endif

}  // namespace nncv

#endif  //! NNCV_BASE_HPP_