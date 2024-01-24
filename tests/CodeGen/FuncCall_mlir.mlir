module @__main {
  func.func private @_lib_nncv_do_something(memref<1x1xf32>)
  func.func @add(%arg0: i32, %arg1: i32) -> i32 {
    %0 = arith.addi %arg0, %arg1 : i32
    return %0 : i32
  }
  func.func private @main() {
    %c8_i32 = arith.constant 8 : i32
    %0 = call @add(%c8_i32, %c8_i32) : (i32, i32) -> i32
    %alloca = memref.alloca() {alignment = 4 : i64} : memref<i32>
    memref.store %0, %alloca[] : memref<i32>
    %alloc = memref.alloc() : memref<1x1xf32>
    call @_lib_nncv_do_something(%alloc) : (memref<1x1xf32>) -> ()
    return
  }
}
