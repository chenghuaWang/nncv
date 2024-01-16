// conv2dHwCB.mlir
// nncv-c test file. Coefficient Broadcasting Algorithm on linalg.conv2d
// AVX2 which split size is 8(8 * 32 = 256)

// %arg0: input
// %arg1: kernel
// %arg2: output
func.func @conv_2d(%arg0: memref<?x?xf32>, %arg1: memref<?x?xf32>, %arg2: memref<?x?xf32>) {
  linalg.conv_2d ins (%arg0, %arg1: memref<?x?xf32>, memref<?x?xf32>)
                 outs (%arg2: memref<?x?xf32>)
  return
}