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
  func.func private @add(%arg0: memref<2048x2048xf32>, %arg1: memref<2048x2048xf32>, %arg2: memref<2048x2048xf32>) {
    affine.for %arg3 = 0 to 2048 {
      affine.for %arg4 = 0 to 2048 {
        %0 = memref.load %arg0[%arg3, %arg4] : memref<2048x2048xf32>
        %1 = memref.load %arg1[%arg3, %arg4] : memref<2048x2048xf32>
        %2 = arith.addf %0, %1 : f32
        memref.store %2, %arg2[%arg3, %arg4] : memref<2048x2048xf32>
      }
    }
    return
  }
  func.func private @init(%arg0: memref<2048x2048xf32>, %arg1: f32) {
    %c1_i32 = arith.constant 1 : i32
    %c2048_i32 = arith.constant 2048 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi slt, %0, %c2048_i32 : i32
      scf.condition(%1)
    } do {
      %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
      memref.store %c0_i32, %alloca_0[] : memref<i32>
      scf.while : () -> () {
        %2 = memref.load %alloca_0[] : memref<i32>
        %3 = arith.cmpi slt, %2, %c2048_i32 : i32
        scf.condition(%3)
      } do {
        %2 = memref.load %alloca[] : memref<i32>
        %3 = memref.load %alloca_0[] : memref<i32>
        %4 = arith.index_cast %2 : i32 to index
        %5 = arith.index_cast %3 : i32 to index
        memref.store %arg1, %arg0[%4, %5] : memref<2048x2048xf32>
        %6 = memref.load %alloca_0[] : memref<i32>
        %7 = arith.addi %6, %c1_i32 : i32
        memref.store %7, %alloca_0[] : memref<i32>
        scf.yield
      }
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.addi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    return
  }
  func.func private @main() {
    %c0 = arith.constant 0 : index
    %cst = arith.constant 2.000000e+00 : f32
    %cst_0 = arith.constant 1.000000e+00 : f32
    %alloc = memref.alloc() : memref<2048x2048xf32>
    %alloc_1 = memref.alloc() : memref<2048x2048xf32>
    %alloc_2 = memref.alloc() : memref<2048x2048xf32>
    call @init(%alloc, %cst_0) : (memref<2048x2048xf32>, f32) -> ()
    call @init(%alloc_1, %cst) : (memref<2048x2048xf32>, f32) -> ()
    %0 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %0, %alloca[] : memref<i64>
    call @add(%alloc, %alloc_1, %alloc_2) : (memref<2048x2048xf32>, memref<2048x2048xf32>, memref<2048x2048xf32>) -> ()
    memref.dealloc %alloc_1 : memref<2048x2048xf32>
    memref.dealloc %alloc : memref<2048x2048xf32>
    %1 = call @_mlir_ciface_nanoTime() : () -> i64
    %alloca_3 = memref.alloca() {alignment = 8 : i64} : memref<i64>
    memref.store %1, %alloca_3[] : memref<i64>
    %2 = memref.load %alloca_3[] : memref<i64>
    %3 = memref.load %alloca[] : memref<i64>
    %4 = arith.subi %2, %3 : i64
    call @printI64(%4) : (i64) -> ()
    call @printNewline() : () -> ()
    %5 = memref.load %alloc_2[%c0, %c0] : memref<2048x2048xf32>
    memref.dealloc %alloc_2 : memref<2048x2048xf32>
    call @printF32(%5) : (f32) -> ()
    call @printNewline() : () -> ()
    return
  }
}
