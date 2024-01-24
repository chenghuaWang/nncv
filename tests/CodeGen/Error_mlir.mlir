module @__main {
  func.func private @testLoopWithEmpty() {
    %c1_i32 = arith.constant 1 : i32
    %c128_i32 = arith.constant 128 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloc = memref.alloc() : memref<128xf32>
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi ult, %0, %c128_i32 : i32
      scf.condition(%1)
    } do {
      %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<f32>
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.index_cast %0 : i32 to index
      %2 = memref.load %alloc[%1] : memref<128xf32>
      memref.store %2, %alloca_0[] : memref<f32>
      %3 = memref.load %alloca[] : memref<i32>
      %4 = arith.addi %3, %c1_i32 : i32
      memref.store %4, %alloca[] : memref<i32>
      scf.yield
    }
    call @testLoopWithEmpty() : () -> ()
    return
  }
}
