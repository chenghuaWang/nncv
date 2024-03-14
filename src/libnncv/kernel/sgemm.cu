#include "libnncv/kernel/sgemm.cuh"

namespace nncv {
namespace rt {
namespace kernel {

// cal offset from row col and ld , in row-major matrix, ld is the width of the matrix
#define OFFSET(row, col, ld) ((row) * (ld) + (col))

// transfer float4
#define FETCH_FLOAT4(pointer) (reinterpret_cast<float4*>(&(pointer))[0])

__global__ void sgemm(float* __restrict__ lhs, float* __restrict__ rhs, float* __restrict__ dst,
                      int m, int n, int k) {
  // get all index needed
  int BX = blockIdx.x;
  int BY = blockIdx.y;
  int TX = threadIdx.x;
  int TY = threadIdx.y;

  // caculate all block based sizes
  const int THREAD_X_PER_BLOCK = BLOCK_SIZE_N / THREAD_SIZE_X;
  const int THREAD_Y_PER_BLOCK = BLOCK_SIZE_M / THREAD_SIZE_Y;
  const int THREAD_NUM_PER_BLOCK = THREAD_X_PER_BLOCK * THREAD_Y_PER_BLOCK;
  const int THIS_THREAD_ID = TY * THREAD_X_PER_BLOCK + TX;

  // how many sizes needed for register. Those for transfer global mem to shared mem.
  // globael mem -> register -> shared mem
  const int lhsTransfer = BLOCK_SIZE_M * BLOCK_SIZE_K / (THREAD_NUM_PER_BLOCK * 4);
  const int rhsTransfer = BLOCK_SIZE_K * BLOCK_SIZE_N / (THREAD_NUM_PER_BLOCK * 4);

  // create transfer register
  float lhsTransferRegister[4 * lhsTransfer];
  float rhsTransferRegister[4 * rhsTransfer];

  // [shared memory]. Double Buffer
  // contained in one block, shared by 16x16=256 threads in one block.
  __shared__ float lhsShared[2][BLOCK_SIZE_K][BLOCK_SIZE_M];  // 8 x 128 by default
  __shared__ float rhsShared[2][BLOCK_SIZE_K][BLOCK_SIZE_N];  // 8 x 128 by default

  // create the accumulate array on [register level]. And init it with 0.
  float accum[THREAD_SIZE_Y][THREAD_SIZE_X];  // 8 x 8 by default
#pragma unroll
  for (int i = 0; i < THREAD_SIZE_Y; i++) {
#pragma unroll
    for (int j = 0; j < THREAD_SIZE_X; j++) { accum[i][j] = 0.f; }
  }

  // create the register array for lhs and rhs. [register level] with double buffer
  float lhsRegister[2][THREAD_SIZE_Y];
  float rhsRegister[2][THREAD_SIZE_X];

  // prepare for transfer
  const int LHS_TILE_THREAD_PER_ROW = BLOCK_SIZE_K / 4;
  const int RHS_TILE_THREAD_PER_ROW = BLOCK_SIZE_N / 4;
  const int LHS_TILE_ROW_START = THIS_THREAD_ID / LHS_TILE_THREAD_PER_ROW;
  const int RHS_TILE_ROW_START = THIS_THREAD_ID / RHS_TILE_THREAD_PER_ROW;
  const int LHS_TILE_COL = THIS_THREAD_ID % LHS_TILE_THREAD_PER_ROW * 4;
  const int RHS_TILE_COL = THIS_THREAD_ID % RHS_TILE_THREAD_PER_ROW * 4;
  const int LHS_TILE_ROW_STRIDE = THREAD_NUM_PER_BLOCK / LHS_TILE_THREAD_PER_ROW;
  const int RHS_TILE_ROW_STRIDE = THREAD_NUM_PER_BLOCK / RHS_TILE_THREAD_PER_ROW;
  lhs = &lhs[(BLOCK_SIZE_M * BY) * k];
  rhs = &rhs[BLOCK_SIZE_N * BX];
  const int warpId = THIS_THREAD_ID / 32;
  const int laneId = THIS_THREAD_ID % 32;
  const int lhsTileIndex = warpId / 2 * 16 + laneId / 8 * 4;
  const int rhsTileIndex = warpId % 2 * 32 + laneId % 8 * 4;

// transfer lhs first tile block to shared memory
#pragma unroll
  for (int i = 0; i < BLOCK_SIZE_M; i += LHS_TILE_ROW_STRIDE) {
    int _idx = i / LHS_TILE_ROW_STRIDE * 4;
    FETCH_FLOAT4(lhsTransferRegister[_idx]) =
        FETCH_FLOAT4(lhs[OFFSET(LHS_TILE_ROW_START + i,  // row
                                LHS_TILE_COL,            // col
                                k)]);
    lhsShared[0][LHS_TILE_COL][LHS_TILE_ROW_START + i] = lhsTransferRegister[_idx];
    lhsShared[0][LHS_TILE_COL + 1][LHS_TILE_ROW_START + i] = lhsTransferRegister[_idx + 1];
    lhsShared[0][LHS_TILE_COL + 2][LHS_TILE_ROW_START + i] = lhsTransferRegister[_idx + 2];
    lhsShared[0][LHS_TILE_COL + 3][LHS_TILE_ROW_START + i] = lhsTransferRegister[_idx + 3];
  }

  //  transfer rhs first tile block to shared memory
#pragma unroll
  for (int i = 0; i < BLOCK_SIZE_K; i += RHS_TILE_ROW_STRIDE) {
    FETCH_FLOAT4(rhsShared[0][RHS_TILE_ROW_START + i][RHS_TILE_COL]) =
        FETCH_FLOAT4(rhs[OFFSET(RHS_TILE_ROW_START + i,  // row
                                RHS_TILE_COL,            // col
                                n)]);
  }
  __syncthreads();

  // load lhs from shared memory to register
  FETCH_FLOAT4(lhsRegister[0][0]) = FETCH_FLOAT4(lhsShared[0][0][lhsTileIndex]);
  FETCH_FLOAT4(lhsRegister[0][4]) = FETCH_FLOAT4(lhsShared[0][0][lhsTileIndex + 64]);

  // load rhs from shared memory to register
  FETCH_FLOAT4(rhsRegister[0][0]) = FETCH_FLOAT4(rhsShared[0][0][rhsTileIndex]);
  FETCH_FLOAT4(rhsRegister[0][4]) = FETCH_FLOAT4(rhsShared[0][0][rhsTileIndex + 64]);
}

#undef OFFSET
#undef FETCH_FLOAT4

}  // namespace kernel
}  // namespace rt
}  // namespace nncv