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
  func.func @ReLU(%arg0: memref<2048x2048xf32>, %arg1: memref<2048x2048xf32>) {
    %c0_i8 = arith.constant 0 : i8
    %cst = arith.constant 0.000000e+00 : f32
    affine.for %arg2 = 0 to 2048 {
      affine.for %arg3 = 0 to 2048 {
        %0 = memref.load %arg0[%arg2, %arg3] : memref<2048x2048xf32>
        %1 = arith.cmpf ogt, %0, %cst : f32
        %2 = arith.extui %1 : i1 to i8
        %3 = arith.cmpi ugt, %2, %c0_i8 : i8
        scf.if %3 {
          %4 = memref.load %arg0[%arg2, %arg3] : memref<2048x2048xf32>
          memref.store %4, %arg1[%arg2, %arg3] : memref<2048x2048xf32>
        } else {
          memref.store %cst, %arg1[%arg2, %arg3] : memref<2048x2048xf32>
        }
      }
    }
    return
  }
  func.func private @main() {
    %alloc = memref.alloc() : memref<2048x2048xf32>
    %alloc_0 = memref.alloc() : memref<2048x2048xf32>
    %0 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %0, %alloca[] : memref<i64>
    call @ReLU(%alloc, %alloc_0) : (memref<2048x2048xf32>, memref<2048x2048xf32>) -> ()
    memref.dealloc %alloc_0 : memref<2048x2048xf32>
    memref.dealloc %alloc : memref<2048x2048xf32>
    %1 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca_1 = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %1, %alloca_1[] : memref<i64>
    %2 = memref.load %alloca_1[] : memref<i64>
    %3 = memref.load %alloca[] : memref<i64>
    %4 = arith.subi %2, %3 : i64
    call @printI64(%4) : (i64) -> ()
    call @printNewline() : () -> ()
    return
  }
}
