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
  func.func private @VecAdd(%arg0: memref<128xf32>, %arg1: memref<128xf32>, %arg2: memref<128xf32>) {
    affine.for %arg3 = 0 to 128 {
      %0 = memref.load %arg0[%arg3] : memref<128xf32>
      %1 = memref.load %arg1[%arg3] : memref<128xf32>
      %2 = arith.addf %0, %1 : f32
      memref.store %2, %arg2[%arg3] : memref<128xf32>
    }
    return
  }
  func.func private @main() {
    %alloc = memref.alloc() : memref<128xf32>
    %alloc_0 = memref.alloc() : memref<128xf32>
    %alloc_1 = memref.alloc() : memref<128xf32>
    %0 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %0, %alloca[] : memref<i64>
    call @VecAdd(%alloc, %alloc_0, %alloc_1) : (memref<128xf32>, memref<128xf32>, memref<128xf32>) -> ()
    memref.dealloc %alloc_1 : memref<128xf32>
    memref.dealloc %alloc_0 : memref<128xf32>
    memref.dealloc %alloc : memref<128xf32>
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
