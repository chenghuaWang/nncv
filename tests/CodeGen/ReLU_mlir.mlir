module @__main {
  func.func @ReLU(%arg0: memref<192x192xf32>, %arg1: memref<192x192xf32>) {
    %c0_i8 = arith.constant 0 : i8
    %cst = arith.constant 0.000000e+00 : f32
    affine.for %arg2 = 0 to 192 {
      affine.for %arg3 = 0 to 192 {
        %0 = memref.load %arg0[%arg2, %arg3] : memref<192x192xf32>
        %1 = arith.cmpf ogt, %0, %cst : f32
        %2 = arith.extui %1 : i1 to i8
        %3 = arith.cmpi ugt, %2, %c0_i8 : i8
        scf.if %3 {
          %4 = memref.load %arg0[%arg2, %arg3] : memref<192x192xf32>
          memref.store %4, %arg1[%arg2, %arg3] : memref<192x192xf32>
        } else {
          memref.store %cst, %arg1[%arg2, %arg3] : memref<192x192xf32>
        }
      }
    }
    return
  }
}
