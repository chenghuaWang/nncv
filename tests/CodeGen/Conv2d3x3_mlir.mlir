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
  func.func private @Conv2d(%arg0: memref<1x3x2048x2048xf32>, %arg1: memref<16x3x3x3xf32>, %arg2: memref<1x16x2046x2046xf32>) {
    %c0 = arith.constant 0 : index
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 2046 {
        affine.for %arg5 = 0 to 2046 {
          affine.for %arg6 = 0 to 3 {
            affine.for %arg7 = 0 to 3 {
              %0 = arith.addi %arg4, %arg7 : index
              affine.for %arg8 = 0 to 3 {
                %1 = memref.load %arg2[%c0, %arg3, %arg4, %arg5] : memref<1x16x2046x2046xf32>
                %2 = arith.addi %arg5, %arg8 : index
                %3 = memref.load %arg0[%c0, %arg6, %0, %2] : memref<1x3x2048x2048xf32>
                %4 = memref.load %arg1[%arg3, %arg6, %arg7, %arg8] : memref<16x3x3x3xf32>
                %5 = arith.mulf %3, %4 : f32
                %6 = arith.addf %1, %5 : f32
                memref.store %6, %arg2[%c0, %arg3, %arg4, %arg5] : memref<1x16x2046x2046xf32>
              }
            }
          }
        }
      }
    }
    return
  }
  func.func private @main() {
    %alloc = memref.alloc() : memref<1x3x2048x2048xf32>
    %alloc_0 = memref.alloc() : memref<16x3x3x3xf32>
    %alloc_1 = memref.alloc() : memref<1x16x2046x2046xf32>
    %0 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %0, %alloca[] : memref<i64>
    call @Conv2d(%alloc, %alloc_0, %alloc_1) : (memref<1x3x2048x2048xf32>, memref<16x3x3x3xf32>, memref<1x16x2046x2046xf32>) -> ()
    memref.dealloc %alloc_1 : memref<1x16x2046x2046xf32>
    memref.dealloc %alloc_0 : memref<16x3x3x3xf32>
    memref.dealloc %alloc : memref<1x3x2048x2048xf32>
    %1 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca_2 = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %1, %alloca_2[] : memref<i64>
    %2 = memref.load %alloca_2[] : memref<i64>
    %3 = memref.load %alloca[] : memref<i64>
    %4 = arith.subi %2, %3 : i64
    call @printI64(%4) : (i64) -> ()
    call @printNewline() : () -> ()
    return
  }
}
