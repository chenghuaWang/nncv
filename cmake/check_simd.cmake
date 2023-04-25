macro(CHECK_SIMD)

  include(CheckCXXSourceRuns)

#-------------------------------------------------------------------------------
# Check Intel SSE
#-------------------------------------------------------------------------------

  set(CMAKE_REQUIRED_FLAGS -msse)
  check_cxx_source_runs(
    "
    #include <immintrin.h>
    int main() {   
      __m128 x;
      x = _mm_set_ps(1.0f,1.0f,1.0f,1.0f);
      return 0;
    }
    " HAVE_SSE)

  if(${HAVE_SSE})
    add_definitions(-DNNCV_HAVE_SSE=1)
    message(STATUS "\tSSE support - yes")
  else()
    message(STATUS "\tSSE support - no")
  endif(${HAVE_SSE})

#-------------------------------------------------------------------------------
# Check Intel AVX2
#-------------------------------------------------------------------------------

  set(CMAKE_REQUIRED_FLAGS -mavx2)
  check_cxx_source_runs(
    "
    #include <immintrin.h>
    int main() {
      int data[8] = {0,0,0,0,0,0,0,0};
      __m256i a = _mm256_loadu_si256((const __m256i *)data);
      __m256i b = _mm256_bslli_epi128(a, 1);
      return 0;
    }
    " HAVE_AVX2)

  if(${HAVE_AVX2})
    add_definitions(-DNNCV_HAVE_AVX2=1)
    message(STATUS "\tAVX2 support - yes")
  else()
    message(STATUS "\tAVX2 support - no")
  endif(${HAVE_AVX2})

#-------------------------------------------------------------------------------
# Check Intel AVX512
#-------------------------------------------------------------------------------

SET(CMAKE_REQUIRED_FLAGS -mavx512f)
check_cxx_source_runs(
  "
  #include <immintrin.h>
  int main() {
    float data[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    __m512 vector = _mm512_loadu_ps(data);
    return 0;
  }
  " HAVE_AVX512)

  if(${HAVE_AVX512})
    add_definitions(-DNNCV_HAVE_AVX512=1)
    message(STATUS "\tAVX512 support - yes")
  else()
    message(STATUS "\tAVX512 support - no")
  endif(${HAVE_AVX512})

#-------------------------------------------------------------------------------
# Check Arm Neon
#-------------------------------------------------------------------------------

  check_cxx_source_runs(
    "
    #include <arm_neon.h>
    int main() {
      float32x4_t a;
      float A[] = {1.0,2.0,3.0,4.0};
      a = vld1q_f32(A);
      return 0;
    }
    " HAVE_NEON)

  if(${HAVE_NEON})
    add_definitions(-DNNCV_HAVE_ARM_NEON=1)
    message(STATUS "\tArm Neon support - yes")
  else()
    message(STATUS "\tArm Neon support - no")
  endif(${HAVE_NEON})

endmacro(CHECK_SIMD)
