module @__main {
  func.func private @declInt32() -> i32 {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c0_i32, %alloca[] : memref<i32>
    %0 = memref.load %alloca[] : memref<i32>
    return %0 : i32
  }
  func.func private @declFloat32() -> f32 {
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<f32>
    %0 = memref.load %alloca[] : memref<f32>
    return %0 : f32
  }
  func.func private @declTensor() -> memref<128x128xf32> {
    %alloc = memref.alloc() : memref<128x128xf32>
    return %alloc : memref<128x128xf32>
  }
  func.func private @assignFloat32() -> f32 {
    %cst = arith.constant 1.200000e+01 : f32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<f32>
    memref.store %cst, %alloca[] : memref<f32>
    %0 = memref.load %alloca[] : memref<f32>
    return %0 : f32
  }
}
