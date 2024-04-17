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
  func.func @MulAdd(%arg0: memref<2048x2048xf32>, %arg1: memref<2048x2048xf32>, %arg2: memref<2048x2048xf32>, %arg3: memref<2048x2048xf32>) {
    affine.for %arg4 = 0 to 2048 {
      affine.for %arg5 = 0 to 2048 {
        %0 = memref.load %arg0[%arg4, %arg5] : memref<2048x2048xf32>
        %1 = memref.load %arg1[%arg4, %arg5] : memref<2048x2048xf32>
        %2 = arith.mulf %0, %1 : f32
        memref.store %2, %arg3[%arg4, %arg5] : memref<2048x2048xf32>
      }
    }
    affine.for %arg4 = 0 to 2048 {
      affine.for %arg5 = 0 to 2048 {
        %0 = memref.load %arg3[%arg4, %arg5] : memref<2048x2048xf32>
        %1 = memref.load %arg2[%arg4, %arg5] : memref<2048x2048xf32>
        %2 = arith.addf %0, %1 : f32
        memref.store %2, %arg3[%arg4, %arg5] : memref<2048x2048xf32>
      }
    }
    return
  }
  func.func private @main() {
    %c0 = arith.constant 0 : index
    %alloc = memref.alloc() : memref<2048x2048xf32>
    %alloc_0 = memref.alloc() : memref<2048x2048xf32>
    %alloc_1 = memref.alloc() : memref<2048x2048xf32>
    %alloc_2 = memref.alloc() : memref<2048x2048xf32>
    %0 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %0, %alloca[] : memref<i64>
    call @MulAdd(%alloc, %alloc_0, %alloc_1, %alloc_2) : (memref<2048x2048xf32>, memref<2048x2048xf32>, memref<2048x2048xf32>, memref<2048x2048xf32>) -> ()
    memref.dealloc %alloc_1 : memref<2048x2048xf32>
    memref.dealloc %alloc_0 : memref<2048x2048xf32>
    memref.dealloc %alloc : memref<2048x2048xf32>
    %1 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca_3 = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %1, %alloca_3[] : memref<i64>
    %2 = memref.load %alloc_2[%c0, %c0] : memref<2048x2048xf32>
    memref.dealloc %alloc_2 : memref<2048x2048xf32>
    call @printF32(%2) : (f32) -> ()
    call @printNewline() : () -> ()
    %3 = memref.load %alloca_3[] : memref<i64>
    %4 = memref.load %alloca[] : memref<i64>
    %5 = arith.subi %3, %4 : i64
    call @printI64(%5) : (i64) -> ()
    call @printNewline() : () -> ()
    return
  }
}
