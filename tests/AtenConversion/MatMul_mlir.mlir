module @__main {
  func.func private @matMul(%arg0: memref<128x128xf32>, %arg1: memref<128x128xf32>, %arg2: memref<128x128xf32>) {
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
      %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
      memref.store %c0_i32, %alloca_0[] : memref<i32>
      scf.while : () -> () {
        %2 = memref.load %alloca_0[] : memref<i32>
        %3 = arith.cmpi ult, %2, %c128_i32 : i32
        scf.condition(%3)
      } do {
        %alloca_1 = memref.alloca() {alignment = 4 : i64} : memref<i32>
        memref.store %c0_i32, %alloca_1[] : memref<i32>
        scf.while : () -> () {
          %4 = memref.load %alloca_1[] : memref<i32>
          %5 = arith.cmpi ult, %4, %c128_i32 : i32
          scf.condition(%5)
        } do {
          %4 = memref.load %alloca[] : memref<i32>
          %5 = memref.load %alloca_0[] : memref<i32>
          %6 = arith.index_cast %4 : i32 to index
          %7 = arith.index_cast %5 : i32 to index
          %8 = memref.load %arg2[%6, %7] : memref<128x128xf32>
          %9 = memref.load %alloca_1[] : memref<i32>
          %10 = arith.index_cast %9 : i32 to index
          %11 = memref.load %arg0[%6, %10] : memref<128x128xf32>
          %12 = memref.load %arg1[%10, %7] : memref<128x128xf32>
          %13 = arith.mulf %11, %12 : f32
          %14 = arith.addf %8, %13 : f32
          memref.store %14, %arg2[%6, %7] : memref<128x128xf32>
          %15 = memref.load %alloca_1[] : memref<i32>
          %16 = arith.addi %15, %c1_i32 : i32
          memref.store %16, %alloca_1[] : memref<i32>
          scf.yield
        }
        %2 = memref.load %alloca_0[] : memref<i32>
        %3 = arith.addi %2, %c1_i32 : i32
        memref.store %3, %alloca_0[] : memref<i32>
        scf.yield
      }
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.addi %0, %c1_i32 : i32
      memref.store %1, %alloca[] : memref<i32>
      scf.yield
    }
    return
  }
}
