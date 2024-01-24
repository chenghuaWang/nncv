module @__main {
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
      %5 = arith.cmpi ult, %4, %c32_i32 : i32
      %6 = arith.extui %5 : i1 to i8
      %alloca_2 = memref.alloca() {alignment = 1 : i64} : memref<i8>
      memref.store %6, %alloca_2[] : memref<i8>
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
    %2 = arith.cmpi ult, %0, %1 : i32
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
      %1 = arith.cmpi ugt, %0, %c0_i32 : i32
      %2 = arith.extui %1 : i1 to i8
      %alloca_0 = memref.alloca() {alignment = 1 : i64} : memref<i8>
      memref.store %2, %alloca_0[] : memref<i8>
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
    %c10_i32 = arith.constant 10 : i32
    %c100_i32 = arith.constant 100 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi ult, %0, %c100_i32 : i32
      %2 = arith.extui %1 : i1 to i8
      %alloca_1 = memref.alloca() {alignment = 1 : i64} : memref<i8>
      memref.store %2, %alloca_1[] : memref<i8>
      scf.condition(%1)
    } do {
      %alloca_1 = memref.alloca() {alignment = 4 : i64} : memref<i32>
      memref.store %c0_i32, %alloca_1[] : memref<i32>
      %0 = memref.load %alloca[] : memref<i32>
      %c1_i32 = arith.constant 1 : i32
      %1 = arith.addi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c10_i32, %alloca_0[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca_0[] : memref<i32>
      %1 = arith.cmpi ugt, %0, %c0_i32 : i32
      %2 = arith.extui %1 : i1 to i8
      %alloca_1 = memref.alloca() {alignment = 1 : i64} : memref<i8>
      memref.store %2, %alloca_1[] : memref<i8>
      scf.condition(%1)
    } do {
      %alloca_1 = memref.alloca() {alignment = 4 : i64} : memref<i32>
      memref.store %c0_i32, %alloca_1[] : memref<i32>
      scf.yield
    }
    return
  }
  func.func private @testWhileUsingInt() {
    %c0_i32 = arith.constant 0 : i32
    %c10_i32 = arith.constant 10 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c10_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi ne, %0, %c0_i32 : i32
      %2 = arith.extui %1 : i1 to i8
      %alloca_0 = memref.alloca() {alignment = 1 : i64} : memref<i8>
      memref.store %2, %alloca_0[] : memref<i8>
      scf.condition(%1)
    } do {
      %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
      memref.store %c0_i32, %alloca_0[] : memref<i32>
      %0 = memref.load %alloca[] : memref<i32>
      %c1_i32 = arith.constant 1 : i32
      %1 = arith.subi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    return
  }
}
