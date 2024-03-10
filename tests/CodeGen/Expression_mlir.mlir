module @__main {
  func.func @testLongArithExpr(%arg0: i32, %arg1: i32) -> i32 {
    %0 = arith.addi %arg0, %arg1 : i32
    %1 = arith.divui %0, %arg0 : i32
    %2 = arith.muli %1, %arg1 : i32
    %3 = arith.addi %2, %0 : i32
    return %3 : i32
  }
  func.func @testArithInt64Expr(%arg0: i64, %arg1: i64) -> i64 {
    %0 = arith.addi %arg0, %arg1 : i64
    return %0 : i64
  }
  func.func @testArithFloat32Expr(%arg0: f32, %arg1: f32) -> f32 {
    %0 = arith.addf %arg0, %arg1 : f32
    return %0 : f32
  }
  func.func @testArithFloat64Expr(%arg0: f64, %arg1: f64) -> f64 {
    %0 = arith.addf %arg0, %arg1 : f64
    return %0 : f64
  }
  func.func @testBoolExpr(%arg0: i32, %arg1: i32) -> i8 {
    %0 = arith.cmpi slt, %arg0, %arg1 : i32
    %1 = arith.extui %0 : i1 to i8
    return %1 : i8
  }
}
