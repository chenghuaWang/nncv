module @__main {
  func.func private @testIf(%arg0: i32, %arg1: i32) -> i32 {
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
}
