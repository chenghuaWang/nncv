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
  func.func private @testFor() -> i8 {
    %c1_i32 = arith.constant 1 : i32
    %c32_i32 = arith.constant 32 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
    %alloca_1 = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca_1[] : memref<i32>
    scf.while : () -> () {
      %4 = memref.load %alloca_1[] : memref<i32>
      %5 = arith.cmpi slt, %4, %c32_i32 : i32
      scf.condition(%5)
    } do {
      %4 = memref.load %alloca[] : memref<i32>
      %5 = arith.addi %4, %c1_i32 : i32
      memref.store %5, %alloca[] : memref<i32>
      %6 = memref.load %alloca_1[] : memref<i32>
      %7 = arith.addi %6, %c1_i32 : i32
      memref.store %7, %alloca_1[] : memref<i32>
      scf.yield
    }
    %0 = memref.load %alloca[] : memref<i32>
    %1 = memref.load %alloca_0[] : memref<i32>
    %2 = arith.cmpi slt, %0, %1 : i32
    %3 = arith.extui %2 : i1 to i8
    return %3 : i8
  }
  func.func private @testWhile() {
    %c2_i32 = arith.constant 2 : i32
    %c0_i32 = arith.constant 0 : i32
    %c16_i32 = arith.constant 16 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c16_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi sgt, %0, %c0_i32 : i32
      scf.condition(%1)
    } do {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.subi %0, %c2_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    return
  }
  func.func private @testLoopWithEmpty() {
    %c1_i32 = arith.constant 1 : i32
    %c100_i32 = arith.constant 100 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi slt, %0, %c100_i32 : i32
      scf.condition(%1)
    } do {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.addi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    return
  }
  func.func private @testWhileUsingInt() {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %c10_i32 = arith.constant 10 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c10_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi ne, %0, %c0_i32 : i32
      scf.condition(%1)
    } do {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.subi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    return
  }
  func.func private @main() {
    %c1_i32 = arith.constant 1 : i32
    %c3_i32 = arith.constant 3 : i32
    %c2_i32 = arith.constant 2 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi slt, %0, %c2_i32 : i32
      %2 = arith.cmpi slt, %0, %c3_i32 : i32
      %3 = arith.andi %1, %2 : i1
      scf.condition(%3)
    } do {
      %alloc = memref.alloc() : memref<1x1xf32>
      %cast = memref.cast %alloc : memref<1x1xf32> to memref<*xf32>
      func.call @printMemrefF32(%cast) : (memref<*xf32>) -> ()
      memref.dealloc %alloc : memref<1x1xf32>
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.addi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    return
  }
}
