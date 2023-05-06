/**
 * @file vm_cuda_error.cuh
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief This file will be included multiple times. Safe guard is not necessary !!!
 * @version 0.1
 * @date 2023-05-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#ifdef NNCV_DEBUG
#define NNCV_CUDA_CALL(F)                                                                      \
  if ((F) != cudaSuccess) {                                                                    \
    printf("Error %s at %s:%d\n", cudaGetErrorString(cudaGetLastError()), __FILE__, __LINE__); \
    exit(-1);                                                                                  \
  }
#define NNCV_CUDA_CHECK()                                                                          \
  if ((cudaPeekAtLastError()) != cudaSuccess) {                                                    \
    printf("Error %s at %s:%d\n", cudaGetErrorString(cudaGetLastError()), __FILE__, __LINE__ - 1); \
    exit(-1);                                                                                      \
  }
#else
#define NNCV_CUDA_CALL(F) (F)
#define NNCV_CUDA_CHECK()
#endif