module @__main {
  func.func private @add(%arg0: memref<128x128xf32>, %arg1: memref<128x128xf32>) -> memref<128x128xf32> {
    %c128_i32 = arith.constant 128 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloc = memref.alloc() : memref<128x128xf32>
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi ult, %0, %c128_i32 : i32
      %2 = arith.extui %1 : i1 to i8
      %alloca_0 = memref.alloca() {alignment = 1 : i64} : memref<i8>
      memref.store %2, %alloca_0[] : memref<i8>
      scf.condition(%1)
    } do {
      %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
      memref.store %c0_i32, %alloca_0[] : memref<i32>
      scf.while : () -> () {
        %2 = memref.load %alloca_0[] : memref<i32>
        %3 = arith.cmpi ult, %2, %c128_i32 : i32
        %4 = arith.extui %3 : i1 to i8
        %alloca_1 = memref.alloca() {alignment = 1 : i64} : memref<i8>
        memref.store %4, %alloca_1[] : memref<i8>
        scf.condition(%3)
      } do {
        %2 = memref.load %alloca[] : memref<i32>
        %3 = memref.load %alloca_0[] : memref<i32>
        %4 = arith.index_cast %2 : i32 to index
        %5 = arith.index_cast %3 : i32 to index
        %6 = memref.load %arg0[%4, %5] : memref<128x128xf32>
        %7 = memref.load %arg1[%4, %5] : memref<128x128xf32>
        %8 = arith.addf %6, %7 : f32
        memref.store %8, %alloc[%4, %5] : memref<128x128xf32>
        %9 = memref.load %alloca_0[] : memref<i32>
        %c1_i32_1 = arith.constant 1 : i32
        %10 = arith.addi %9, %c1_i32_1 : i32
        memref.store %10, %alloca_0[] : memref<i32>
        scf.yield
      }
      %0 = memref.load %alloca[] : memref<i32>
      %c1_i32 = arith.constant 1 : i32
      %1 = arith.addi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    return %alloc : memref<128x128xf32>
  }
}
