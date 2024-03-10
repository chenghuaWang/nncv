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
  func.func private @_partion(%arg0: memref<6xi32>, %arg1: i32, %arg2: i32) -> i32 {
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %arg1, %alloca[] : memref<i32>
    %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %arg2, %alloca_0[] : memref<i32>
    %0 = memref.load %alloca[] : memref<i32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %arg0[%1] : memref<6xi32>
    %alloca_1 = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %2, %alloca_1[] : memref<i32>
    scf.while : () -> () {
      %7 = memref.load %alloca[] : memref<i32>
      %8 = memref.load %alloca_0[] : memref<i32>
      %9 = arith.cmpi slt, %7, %8 : i32
      scf.condition(%9)
    } do {
      scf.while : () -> () {
        %17 = memref.load %alloca[] : memref<i32>
        %18 = memref.load %alloca_0[] : memref<i32>
        %19 = arith.cmpi slt, %17, %18 : i32
        %20 = arith.index_cast %18 : i32 to index
        %21 = memref.load %arg0[%20] : memref<6xi32>
        %22 = memref.load %alloca_1[] : memref<i32>
        %23 = arith.cmpi sge, %21, %22 : i32
        %24 = arith.andi %19, %23 : i1
        scf.condition(%24)
      } do {
        %17 = memref.load %alloca_0[] : memref<i32>
        %18 = arith.subi %17, %c1_i32 : i32
        memref.store %18, %alloca_0[] : memref<i32>
        scf.yield
      }
      %7 = memref.load %alloca[] : memref<i32>
      %8 = arith.index_cast %7 : i32 to index
      %9 = memref.load %alloca_0[] : memref<i32>
      %10 = arith.index_cast %9 : i32 to index
      %11 = memref.load %arg0[%10] : memref<6xi32>
      memref.store %11, %arg0[%8] : memref<6xi32>
      scf.while : () -> () {
        %17 = memref.load %alloca[] : memref<i32>
        %18 = memref.load %alloca_0[] : memref<i32>
        %19 = arith.cmpi slt, %17, %18 : i32
        %20 = arith.index_cast %17 : i32 to index
        %21 = memref.load %arg0[%20] : memref<6xi32>
        %22 = memref.load %alloca_1[] : memref<i32>
        %23 = arith.cmpi sle, %21, %22 : i32
        %24 = arith.andi %19, %23 : i1
        scf.condition(%24)
      } do {
        %17 = memref.load %alloca[] : memref<i32>
        %18 = arith.addi %17, %c1_i32 : i32
        memref.store %18, %alloca[] : memref<i32>
        scf.yield
      }
      %12 = memref.load %alloca_0[] : memref<i32>
      %13 = arith.index_cast %12 : i32 to index
      %14 = memref.load %alloca[] : memref<i32>
      %15 = arith.index_cast %14 : i32 to index
      %16 = memref.load %arg0[%15] : memref<6xi32>
      memref.store %16, %arg0[%13] : memref<6xi32>
      scf.yield
    }
    %3 = memref.load %alloca[] : memref<i32>
    %4 = arith.index_cast %3 : i32 to index
    %5 = memref.load %alloca_1[] : memref<i32>
    memref.store %5, %arg0[%4] : memref<6xi32>
    %6 = memref.load %alloca[] : memref<i32>
    return %6 : i32
  }
  func.func private @QuickSort(%arg0: memref<6xi32>, %arg1: i32, %arg2: i32) {
    %c0_i8 = arith.constant 0 : i8
    %c1_i32 = arith.constant 1 : i32
    %0 = arith.cmpi slt, %arg1, %arg2 : i32
    %1 = arith.extui %0 : i1 to i8
    %2 = arith.cmpi ugt, %1, %c0_i8 : i8
    scf.if %2 {
      %3 = func.call @_partion(%arg0, %arg1, %arg2) : (memref<6xi32>, i32, i32) -> i32
      %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
      memref.store %3, %alloca[] : memref<i32>
      %4 = memref.load %alloca[] : memref<i32>
      %5 = arith.subi %4, %c1_i32 : i32
      func.call @QuickSort(%arg0, %arg1, %5) : (memref<6xi32>, i32, i32) -> ()
      %6 = memref.load %alloca[] : memref<i32>
      %7 = arith.addi %6, %c1_i32 : i32
      func.call @QuickSort(%arg0, %7, %arg2) : (memref<6xi32>, i32, i32) -> ()
    }
    return
  }
  func.func private @main() {
    %c1_i32 = arith.constant 1 : i32
    %c5_i32 = arith.constant 5 : i32
    %c6_i32 = arith.constant 6 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloc = memref.alloc() : memref<6xi32>
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    scf.while : () -> () {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.cmpi slt, %0, %c6_i32 : i32
      scf.condition(%1)
    } do {
      %0 = memref.load %alloca[] : memref<i32>
      %1 = arith.index_cast %0 : i32 to index
      %2 = arith.subi %c6_i32, %0 : i32
      memref.store %2, %alloc[%1] : memref<6xi32>
      %3 = memref.load %alloca[] : memref<i32>
      %4 = arith.addi %3, %c1_i32 : i32
      memref.store %4, %alloca[] : memref<i32>
      scf.yield
    }
    %cast = memref.cast %alloc : memref<6xi32> to memref<*xi32>
    call @printMemrefI32(%cast) : (memref<*xi32>) -> ()
    call @QuickSort(%alloc, %c0_i32, %c5_i32) : (memref<6xi32>, i32, i32) -> ()
    call @printMemrefI32(%cast) : (memref<*xi32>) -> ()
    memref.dealloc %alloc : memref<6xi32>
    return
  }
}
