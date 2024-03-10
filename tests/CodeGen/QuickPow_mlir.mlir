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
  func.func private @QuickPow(%arg0: i32, %arg1: i32) -> i32 {
    %c0_i8 = arith.constant 0 : i8
    %c2_i32 = arith.constant 2 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    %0 = arith.cmpi eq, %arg1, %c0_i32 : i32
    %1 = arith.extui %0 : i1 to i8
    %2 = arith.cmpi ugt, %1, %c0_i8 : i8
    scf.if %2 {
      memref.store %c1_i32, %alloca[] : memref<i32>
    } else {
      %4 = arith.remui %arg1, %c2_i32 : i32
      %5 = arith.cmpi eq, %4, %c1_i32 : i32
      %6 = arith.extui %5 : i1 to i8
      %7 = arith.cmpi ugt, %6, %c0_i8 : i8
      scf.if %7 {
        %8 = arith.subi %arg1, %c1_i32 : i32
        %9 = func.call @QuickPow(%arg0, %8) : (i32, i32) -> i32
        %10 = arith.muli %9, %arg0 : i32
        memref.store %10, %alloca[] : memref<i32>
      } else {
        %8 = arith.divui %arg1, %c2_i32 : i32
        %9 = func.call @QuickPow(%arg0, %8) : (i32, i32) -> i32
        %alloca_0 = memref.alloca() {alignment = 4 : i64} : memref<i32>
        memref.store %9, %alloca_0[] : memref<i32>
        %10 = memref.load %alloca_0[] : memref<i32>
        %11 = arith.muli %10, %10 : i32
        memref.store %11, %alloca[] : memref<i32>
      }
    }
    %3 = memref.load %alloca[] : memref<i32>
    return %3 : i32
  }
  func.func private @main() {
    %c2_i32 = arith.constant 2 : i32
    %c10_i32 = arith.constant 10 : i32
    %0 = call @QuickPow(%c2_i32, %c10_i32) : (i32, i32) -> i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %0, %alloca[] : memref<i32>
    %1 = memref.load %alloca[] : memref<i32>
    %2 = arith.extsi %1 : i32 to i64
    call @printI64(%2) : (i64) -> ()
    return
  }
}
