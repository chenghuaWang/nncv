module @__main {
  func.func private @none()
  func.func private @noneWithRet() -> i32
  func.func private @withoutRetValue(i32, i32, i32, i32)
  func.func private @withRetValue(i32, i32, i32, i32) -> i32
  func.func private @mulTensor(%arg0: memref<64x64xf32>, %arg1: memref<64x64xf32>, %arg2: memref<64x64xf32>) {
    %c42_i32 = arith.constant 42 : i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %c42_i32, %alloca[] : memref<i32>
    return
  }
}
