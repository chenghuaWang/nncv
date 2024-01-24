module @__main {
  func.func private @declTensor() -> memref<8x8x8xf32> {
    %alloc = memref.alloc() : memref<8x8x8xf32>
    return %alloc : memref<8x8x8xf32>
  }
  func.func private @declInt() -> i32 {
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    %0 = memref.load %alloca[] : memref<i32>
    return %0 : i32
  }
  func.func private @declFloat() -> f32 {
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<f32>
    %0 = memref.load %alloca[] : memref<f32>
    return %0 : f32
  }
  func.func private @declBool() -> i8 {
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i8>
    %0 = memref.load %alloca[] : memref<i8>
    return %0 : i8
  }
}
