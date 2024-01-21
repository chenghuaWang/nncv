module {
  func.func @testMatMulDefault(%arg0: memref<720x720xf32>, %arg1: memref<720x720xf32>, %arg2: memref<720x720xf32>) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c8 = arith.constant 8 : index
    %cst = arith.constant 0.000000e+00 : f32
    %0 = vector.splat %cst : vector<8xf32>
    %dim = memref.dim %arg0, %c0 : memref<720x720xf32>
    %dim_0 = memref.dim %arg1, %c0 : memref<720x720xf32>
    %dim_1 = memref.dim %arg1, %c1 : memref<720x720xf32>
    affine.for %arg3 = affine_map<(d0) -> (d0)>(%c0) to affine_map<(d0) -> (d0)>(%dim_0) {
      affine.for %arg4 = affine_map<(d0) -> (d0)>(%c0) to affine_map<(d0) -> (d0)>(%dim) {
        affine.for %arg5 = affine_map<(d0) -> (d0)>(%c0) to affine_map<(d0) -> (d0 ceildiv 8)>(%dim_1) {
          %1 = memref.load %arg0[%arg4, %arg3] : memref<720x720xf32>
          %2 = vector.broadcast %1 : f32 to vector<8xf32>
          %3 = arith.muli %arg5, %c8 : index
          %4 = arith.subi %dim_1, %3 : index
          %5 = arith.cmpi sge, %4, %c8 : index
          scf.if %5 {
            %6 = affine.vector_load %arg1[%arg3, %arg5 * 8] : memref<720x720xf32>, vector<8xf32>
            %7 = affine.vector_load %arg2[%arg4, %arg5 * 8] : memref<720x720xf32>, vector<8xf32>
            %8 = vector.fma %2, %6, %7 : vector<8xf32>
            affine.vector_store %8, %arg2[%arg4, %arg5 * 8] : memref<720x720xf32>, vector<8xf32>
          } else {
            %6 = vector.create_mask %4 : vector<8xi1>
            %7 = arith.muli %arg5, %c8 : index
            %8 = vector.maskedload %arg1[%arg3, %7], %6, %0 : memref<720x720xf32>, vector<8xi1>, vector<8xf32> into vector<8xf32>
            %9 = vector.maskedload %arg2[%arg4, %7], %6, %0 : memref<720x720xf32>, vector<8xi1>, vector<8xf32> into vector<8xf32>
            %10 = vector.fma %2, %8, %9 : vector<8xf32>
            vector.maskedstore %arg2[%arg4, %7], %6, %10 : memref<720x720xf32>, vector<8xi1>, vector<8xf32>
          }
        }
      }
    }
    return
  }
}