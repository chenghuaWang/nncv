module @__main {
  func.func private @matmul(%arg0: memref<512x512xf32>, %arg1: memref<512x512xf32>, %arg2: memref<512x512xf32>) {
    affine.for %arg3 = 0 to 512 {
      affine.for %arg4 = 0 to 512 {
        affine.for %arg5 = 0 to 512 {
          %0 = memref.load %arg2[%arg3, %arg4] : memref<512x512xf32>
          %1 = memref.load %arg0[%arg3, %arg5] : memref<512x512xf32>
          %2 = memref.load %arg1[%arg5, %arg4] : memref<512x512xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          memref.store %4, %arg2[%arg3, %arg4] : memref<512x512xf32>
        }
      }
    }
    return
  }
  func.func private @main() {
    %alloc = memref.alloc() : memref<512x512xf32>
    %alloc_0 = memref.alloc() : memref<512x512xf32>
    %alloc_1 = memref.alloc() : memref<512x512xf32>
    call @matmul(%alloc, %alloc_0, %alloc_1) : (memref<512x512xf32>, memref<512x512xf32>, memref<512x512xf32>) -> ()
    return
  }
}
