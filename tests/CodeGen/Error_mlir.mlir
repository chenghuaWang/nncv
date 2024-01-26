module @__main {
  func.func private @testLoopWithEmpty() {
    %c1_i32 = arith.constant 1 : i32
    %c128_i32 = arith.constant 128 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi ult, %0, %c128_i32 : i32
      scf.condition(%1)
    } do {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.addi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    call @testLoopWithEmpty() : () -> ()
    return
  }
}
