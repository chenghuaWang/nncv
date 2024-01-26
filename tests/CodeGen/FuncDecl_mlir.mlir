module @__main {
  func.func private @none()
  func.func private @noneWithRet() -> i32
  func.func private @withoutRetValue(i32, i32, i32, i32)
  func.func private @withRetValue(i32, i32, i32, i32) -> i32
  func.func private @mulTensor(%arg0: memref<64x64xf32>, %arg1: memref<64x64xf32>, %arg2: memref<64x64xf32>) {
    return
  }
}
