module @__main {
  func.func private @printMemrefF64(memref<*xf64>)
  func.func private @printMemrefF32(memref<*xf32>)
  func.func private @printMemrefF16(memref<*xf16>)
  func.func private @printMemrefI64(memref<*xi64>)
  func.func private @printMemrefI32(memref<*xi32>)
  func.func private @printMemrefI16(memref<*xi16>)
  func.func private @matmul(%arg0: memref<6x6xf32>, %arg1: memref<6x6xf32>, %arg2: memref<6x6xf32>) {
    affine.for %arg3 = 0 to 6 {
      affine.for %arg4 = 0 to 6 {
        affine.for %arg5 = 0 to 6 {
          %0 = memref.load %arg2[%arg3, %arg4] : memref<6x6xf32>
          %1 = memref.load %arg0[%arg3, %arg5] : memref<6x6xf32>
          %2 = memref.load %arg1[%arg5, %arg4] : memref<6x6xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          memref.store %4, %arg2[%arg3, %arg4] : memref<6x6xf32>
        }
      }
    }
    return
  }
  func.func private @initTensor(%arg0: memref<6x6xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    affine.for %arg1 = 0 to 6 {
      affine.for %arg2 = 0 to 6 {
        memref.store %cst, %arg0[%arg1, %arg2] : memref<6x6xf32>
      }
    }
    return
  }
  func.func private @initEyeTensor(%arg0: memref<6x6xf32>, %arg1: f32) {
    %c0_i8 = arith.constant 0 : i8
    %cst = arith.constant 0.000000e+00 : f32
    affine.for %arg2 = 0 to 6 {
      %0 = arith.index_cast %arg2 : index to i64
      affine.for %arg3 = 0 to 6 {
        %1 = arith.index_cast %arg3 : index to i64
        %2 = arith.cmpi eq, %0, %1 : i64
        %3 = arith.extui %2 : i1 to i8
        %4 = arith.cmpi ugt, %3, %c0_i8 : i8
        scf.if %4 {
          memref.store %arg1, %arg0[%arg2, %arg3] : memref<6x6xf32>
        } else {
          memref.store %cst, %arg0[%arg2, %arg3] : memref<6x6xf32>
        }
      }
    }
    return
  }
  func.func private @fillTensor(%arg0: memref<6x6xf32>, %arg1: f32) {
    %cst = arith.constant 6.666000e+00 : f32
    affine.for %arg2 = 0 to 6 {
      affine.for %arg3 = 0 to 6 {
        memref.store %cst, %arg0[%arg2, %arg3] : memref<6x6xf32>
      }
    }
    return
  }
  func.func private @main() {
    %cst = arith.constant 6.666660e+00 : f32
    %cst_0 = arith.constant 3.000000e+00 : f32
    %cst_1 = arith.constant 2.000000e+00 : f32
    %alloc = memref.alloc() : memref<6x6xf32>
    %alloc_2 = memref.alloc() : memref<6x6xf32>
    %alloc_3 = memref.alloc() : memref<6x6xf32>
    call @initEyeTensor(%alloc, %cst_1) : (memref<6x6xf32>, f32) -> ()
    call @initEyeTensor(%alloc_2, %cst_0) : (memref<6x6xf32>, f32) -> ()
    call @initTensor(%alloc_3) : (memref<6x6xf32>) -> ()
    call @matmul(%alloc, %alloc_2, %alloc_3) : (memref<6x6xf32>, memref<6x6xf32>, memref<6x6xf32>) -> ()
    %cast = memref.cast %alloc_3 : memref<6x6xf32> to memref<*xf32>
    call @printMemrefF32(%cast) : (memref<*xf32>) -> ()
    call @fillTensor(%alloc_3, %cst) : (memref<6x6xf32>, f32) -> ()
    call @printMemrefF32(%cast) : (memref<*xf32>) -> ()
    return
  }
}
