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
  func.func private @main() {
    %cst = arith.constant -1.000000e+00 : f32
    %cst_0 = arith.constant 3.000000e+00 : f32
    %cst_1 = arith.constant 2.000000e+00 : f32
    %cst_2 = arith.constant 1.000000e+00 : f32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<f32>
    memref.store %cst_2, %alloca[] : memref<f32>
    %alloca_3 = memref.alloca() {alignment = 4 : i64} : memref<f32>
    memref.store %cst_1, %alloca_3[] : memref<f32>
    %alloca_4 = memref.alloca() {alignment = 4 : i64} : memref<f32>
    memref.store %cst_0, %alloca_4[] : memref<f32>
    %alloca_5 = memref.alloca() {alignment = 4 : i64} : memref<f32>
    memref.store %cst, %alloca_5[] : memref<f32>
    %0 = memref.load %alloca_5[] : memref<f32>
    %1 = math.absf %0 : f32
    call @printF32(%1) : (f32) -> ()
    call @printNewline() : () -> ()
    %2 = memref.load %alloca[] : memref<f32>
    %3 = math.exp %2 : f32
    call @printF32(%3) : (f32) -> ()
    call @printNewline() : () -> ()
    %4 = memref.load %alloca_3[] : memref<f32>
    %5 = math.exp %4 : f32
    call @printF32(%5) : (f32) -> ()
    call @printNewline() : () -> ()
    %6 = memref.load %alloca_5[] : memref<f32>
    %7 = math.exp %6 : f32
    call @printF32(%7) : (f32) -> ()
    call @printNewline() : () -> ()
    %8 = memref.load %alloca[] : memref<f32>
    %9 = math.exp2 %8 : f32
    call @printF32(%9) : (f32) -> ()
    call @printNewline() : () -> ()
    %10 = memref.load %alloca_4[] : memref<f32>
    %11 = math.exp2 %10 : f32
    call @printF32(%11) : (f32) -> ()
    call @printNewline() : () -> ()
    %12 = math.fma %cst_2, %cst_1, %cst_0 : f32
    call @printF32(%12) : (f32) -> ()
    call @printNewline() : () -> ()
    return
  }
}
