module @__main {
  func.func private @testIfWoElse(%arg0: i32, %arg1: i32) -> i32 {
    %c0_i8 = arith.constant 0 : i8
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    %0 = arith.cmpi ult, %arg0, %arg1 : i32
    %1 = arith.extui %0 : i1 to i8
    %2 = arith.cmpi ugt, %1, %c0_i8 : i8
    scf.if %2 {
      %4 = arith.addi %arg0, %arg1 : i32
      memref.store %4, %alloca[] : memref<i32>
    }
    %3 = memref.load %alloca[] : memref<i32>
    return %3 : i32
  }
  func.func private @testIfWElse(%arg0: i32, %arg1: i32) -> i32 {
    %c0_i8 = arith.constant 0 : i8
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    %0 = arith.cmpi ult, %arg0, %arg1 : i32
    %1 = arith.extui %0 : i1 to i8
    %2 = arith.cmpi ugt, %1, %c0_i8 : i8
    scf.if %2 {
      %4 = arith.addi %arg0, %arg1 : i32
      memref.store %4, %alloca[] : memref<i32>
    } else {
      %4 = arith.subi %arg0, %arg1 : i32
      memref.store %4, %alloca[] : memref<i32>
    }
    %3 = memref.load %alloca[] : memref<i32>
    return %3 : i32
  }
  func.func private @testNestedIf() -> i8 {
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
    %0 = memref.load %alloca[] : memref<i32>
    %1 = memref.load %alloca_0[] : memref<i32>
    %2 = arith.cmpi ult, %0, %1 : i32
    %3 = arith.extui %2 : i1 to i8
    return %3 : i8
  }
  func.func private @testIfWBreak(%arg0: i32, %arg1: i32) -> i32 {
    %c0_i8 = arith.constant 0 : i8
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    %0 = arith.cmpi ult, %arg0, %arg1 : i32
    %1 = arith.extui %0 : i1 to i8
    %2 = arith.cmpi ugt, %1, %c0_i8 : i8
    scf.if %2 {
      %4 = arith.addi %arg0, %arg1 : i32
      memref.store %4, %alloca[] : memref<i32>
    }
    %3 = memref.load %alloca[] : memref<i32>
    return %3 : i32
  }
  func.func private @testIntInIfCondition(%arg0: i32) -> i32 {
    %c1_i32 = arith.constant 1 : i32
    %c0_i8 = arith.constant 0 : i8
    %c0_i32 = arith.constant 0 : i32
    %c42_i32 = arith.constant 42 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c42_i32, %alloca[] : memref<i32>
    %0 = arith.cmpi ne, %arg0, %c0_i32 : i32
    %1 = arith.extui %0 : i1 to i8
    %2 = arith.cmpi ugt, %1, %c0_i8 : i8
    scf.if %2 {
      %4 = memref.load %alloca[] : memref<i32>
      %5 = arith.addi %4, %c1_i32 : i32
      memref.store %5, %alloca[] : memref<i32>
    }
    %3 = memref.load %alloca[] : memref<i32>
    return %3 : i32
  }
}
