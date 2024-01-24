module @__main {
  func.func private @main() {
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<f32>
    %alloc = memref.alloc() : memref<42x42xf32>
    %0 = arith.index_cast %c1_i32 : i32 to index
    %1 = memref.load %alloc[%0, %0] : memref<42x42xf32>
    memref.store %1, %alloca[] : memref<f32>
    return
  }
}
