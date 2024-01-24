module @__main {
  func.func private @addI(%arg0: i32, %arg1: i32) -> i32 {
    %0 = arith.addi %arg0, %arg1 : i32
    return %0 : i32
  }
  func.func private @minusI(%arg0: i32, %arg1: i32) -> i32 {
    %0 = arith.subi %arg0, %arg1 : i32
    return %0 : i32
  }
  func.func private @divI(%arg0: i32, %arg1: i32) -> i32 {
    %0 = arith.divui %arg0, %arg1 : i32
    return %0 : i32
  }
  func.func private @mulI(%arg0: i32, %arg1: i32) -> i32 {
    %0 = arith.muli %arg0, %arg1 : i32
    return %0 : i32
  }
  func.func private @addF(%arg0: f32, %arg1: f32) -> f32 {
    %0 = arith.addf %arg0, %arg1 : f32
    return %0 : f32
  }
  func.func private @minusF(%arg0: f32, %arg1: f32) -> f32 {
    %0 = arith.subf %arg0, %arg1 : f32
    return %0 : f32
  }
  func.func private @divF(%arg0: f32, %arg1: f32) -> f32 {
    %0 = arith.divf %arg0, %arg1 : f32
    return %0 : f32
  }
  func.func private @mulF(%arg0: f32, %arg1: f32) -> f32 {
    %0 = arith.mulf %arg0, %arg1 : f32
    return %0 : f32
  }
  func.func private @cmpL(%arg0: i32, %arg1: i32) -> i8 {
    %0 = arith.cmpi ult, %arg0, %arg1 : i32
    %1 = arith.extui %0 : i1 to i8
    return %1 : i8
  }
  func.func private @cmpG(%arg0: i32, %arg1: i32) -> i8 {
    %0 = arith.cmpi ugt, %arg0, %arg1 : i32
    %1 = arith.extui %0 : i1 to i8
    return %1 : i8
  }
}
