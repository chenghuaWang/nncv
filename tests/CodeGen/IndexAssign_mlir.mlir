module @__main {
  func.func private @main() {
    %c1 = arith.constant 1 : index
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<f32>
    %alloc = memref.alloc() : memref<42x42xf32>
    %0 = memref.load %alloc[%c1, %c1] : memref<42x42xf32>
    memref.store %0, %alloca[] : memref<f32>
    return
  }
}
