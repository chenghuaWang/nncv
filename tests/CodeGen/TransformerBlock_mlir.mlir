module @__main {
  func.func private @printMemrefF64(memref<*xf64>)
  func.func private @printMemrefF32(memref<*xf32>)
  func.func private @printMemrefF16(memref<*xf16>)
  func.func private @printMemrefI64(memref<*xi64>)
  func.func private @printMemrefI32(memref<*xi32>)
  func.func private @printMemrefI16(memref<*xi16>)
  func.func private @printI64(i64)
  func.func private @printF32(f32)
  func.func private @printF64(f32)
  func.func private @_mlir_ciface_nanoTime() -> i64
  func.func private @printNewline()
  func.func private @Linear(%arg0: memref<1024x2048xf32>, %arg1: memref<2048x2048xf32>, %arg2: memref<1024x2048xf32>) {
    affine.for %arg3 = 0 to 1024 {
      affine.for %arg4 = 0 to 2048 {
        affine.for %arg5 = 0 to 2048 {
          %0 = memref.load %arg2[%arg3, %arg4] : memref<1024x2048xf32>
          %1 = memref.load %arg0[%arg3, %arg5] : memref<1024x2048xf32>
          %2 = memref.load %arg1[%arg5, %arg4] : memref<2048x2048xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          memref.store %4, %arg2[%arg3, %arg4] : memref<1024x2048xf32>
        }
      }
    }
    return
  }
  func.func private @DivideEleWise(%arg0: memref<1024x1024xf32>, %arg1: f32) {
    affine.for %arg2 = 0 to 1024 {
      affine.for %arg3 = 0 to 1024 {
        %0 = memref.load %arg0[%arg2, %arg3] : memref<1024x1024xf32>
        %1 = arith.divf %0, %arg1 : f32
        memref.store %1, %arg0[%arg2, %arg3] : memref<1024x1024xf32>
      }
    }
    return
  }
  func.func private @Transpose(%arg0: memref<1024x2048xf32>, %arg1: memref<2048x1024xf32>) {
    affine.for %arg2 = 0 to 1024 {
      affine.for %arg3 = 0 to 2048 {
        %0 = memref.load %arg0[%arg2, %arg3] : memref<1024x2048xf32>
        memref.store %0, %arg1[%arg3, %arg2] : memref<2048x1024xf32>
      }
    }
    return
  }
  func.func private @CalAttentionWeight(%arg0: memref<1024x2048xf32>, %arg1: memref<2048x1024xf32>, %arg2: memref<1024x1024xf32>) {
    affine.for %arg3 = 0 to 1024 {
      affine.for %arg4 = 0 to 1024 {
        affine.for %arg5 = 0 to 2048 {
          %0 = memref.load %arg2[%arg3, %arg4] : memref<1024x1024xf32>
          %1 = memref.load %arg0[%arg3, %arg5] : memref<1024x2048xf32>
          %2 = memref.load %arg1[%arg5, %arg4] : memref<2048x1024xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          memref.store %4, %arg2[%arg3, %arg4] : memref<1024x1024xf32>
        }
      }
    }
    return
  }
  func.func private @CalAttenedValue(%arg0: memref<1024x1024xf32>, %arg1: memref<1024x2048xf32>, %arg2: memref<1024x2048xf32>) {
    affine.for %arg3 = 0 to 1024 {
      affine.for %arg4 = 0 to 2048 {
        affine.for %arg5 = 0 to 1024 {
          %0 = memref.load %arg2[%arg3, %arg4] : memref<1024x2048xf32>
          %1 = memref.load %arg0[%arg3, %arg5] : memref<1024x1024xf32>
          %2 = memref.load %arg1[%arg5, %arg4] : memref<1024x2048xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          memref.store %4, %arg2[%arg3, %arg4] : memref<1024x2048xf32>
        }
      }
    }
    return
  }
  func.func private @Softmax(%arg0: memref<1024x1024xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    affine.for %arg1 = 0 to 1024 {
      %alloca = memref.alloca() {alignment = 4 : i64} : memref<f32>
      memref.store %cst, %alloca[] : memref<f32>
      affine.for %arg2 = 0 to 1024 {
        %0 = memref.load %alloca[] : memref<f32>
        %1 = memref.load %arg0[%arg1, %arg2] : memref<1024x1024xf32>
        %2 = math.exp %1 : f32
        %3 = arith.addf %0, %2 : f32
        memref.store %3, %alloca[] : memref<f32>
      }
      affine.for %arg2 = 0 to 1024 {
        %0 = memref.load %arg0[%arg1, %arg2] : memref<1024x1024xf32>
        %1 = math.exp %0 : f32
        %2 = memref.load %alloca[] : memref<f32>
        %3 = arith.divf %1, %2 : f32
        memref.store %3, %arg0[%arg1, %arg2] : memref<1024x1024xf32>
      }
    }
    return
  }
  func.func private @main() {
    %c0 = arith.constant 0 : index
    %cst = arith.constant 6.400000e+01 : f32
    %0 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %0, %alloca[] : memref<i64>
    %alloc = memref.alloc() : memref<1024x2048xf32>
    %alloc_0 = memref.alloc() : memref<2048x2048xf32>
    %alloc_1 = memref.alloc() : memref<2048x2048xf32>
    %alloc_2 = memref.alloc() : memref<2048x2048xf32>
    %alloc_3 = memref.alloc() : memref<1024x2048xf32>
    %alloc_4 = memref.alloc() : memref<1024x2048xf32>
    %alloc_5 = memref.alloc() : memref<1024x2048xf32>
    call @Linear(%alloc, %alloc_0, %alloc_3) : (memref<1024x2048xf32>, memref<2048x2048xf32>, memref<1024x2048xf32>) -> ()
    memref.dealloc %alloc_0 : memref<2048x2048xf32>
    call @Linear(%alloc, %alloc_1, %alloc_4) : (memref<1024x2048xf32>, memref<2048x2048xf32>, memref<1024x2048xf32>) -> ()
    memref.dealloc %alloc_1 : memref<2048x2048xf32>
    call @Linear(%alloc, %alloc_2, %alloc_5) : (memref<1024x2048xf32>, memref<2048x2048xf32>, memref<1024x2048xf32>) -> ()
    memref.dealloc %alloc_2 : memref<2048x2048xf32>
    memref.dealloc %alloc : memref<1024x2048xf32>
    %alloc_6 = memref.alloc() : memref<2048x1024xf32>
    %alloc_7 = memref.alloc() : memref<1024x1024xf32>
    call @Transpose(%alloc_4, %alloc_6) : (memref<1024x2048xf32>, memref<2048x1024xf32>) -> ()
    memref.dealloc %alloc_4 : memref<1024x2048xf32>
    call @CalAttentionWeight(%alloc_3, %alloc_6, %alloc_7) : (memref<1024x2048xf32>, memref<2048x1024xf32>, memref<1024x1024xf32>) -> ()
    memref.dealloc %alloc_6 : memref<2048x1024xf32>
    memref.dealloc %alloc_3 : memref<1024x2048xf32>
    call @DivideEleWise(%alloc_7, %cst) : (memref<1024x1024xf32>, f32) -> ()
    call @Softmax(%alloc_7) : (memref<1024x1024xf32>) -> ()
    %alloc_8 = memref.alloc() : memref<1024x2048xf32>
    call @CalAttenedValue(%alloc_7, %alloc_5, %alloc_8) : (memref<1024x1024xf32>, memref<1024x2048xf32>, memref<1024x2048xf32>) -> ()
    memref.dealloc %alloc_7 : memref<1024x1024xf32>
    memref.dealloc %alloc_5 : memref<1024x2048xf32>
    %alloc_9 = memref.alloc() : memref<2048x2048xf32>
    %alloc_10 = memref.alloc() : memref<1024x2048xf32>
    call @Linear(%alloc_8, %alloc_9, %alloc_10) : (memref<1024x2048xf32>, memref<2048x2048xf32>, memref<1024x2048xf32>) -> ()
    memref.dealloc %alloc_9 : memref<2048x2048xf32>
    memref.dealloc %alloc_8 : memref<1024x2048xf32>
    %1 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca_11 = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %1, %alloca_11[] : memref<i64>
    %2 = memref.load %alloc_10[%c0, %c0] : memref<1024x2048xf32>
    memref.dealloc %alloc_10 : memref<1024x2048xf32>
    call @printF32(%2) : (f32) -> ()
    call @printNewline() : () -> ()
    %3 = memref.load %alloca_11[] : memref<i64>
    %4 = memref.load %alloca[] : memref<i64>
    %5 = arith.subi %3, %4 : i64
    call @printI64(%5) : (i64) -> ()
    call @printNewline() : () -> ()
    return
  }
}
