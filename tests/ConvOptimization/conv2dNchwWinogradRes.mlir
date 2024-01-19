module {
  func.func @conv_16433136(%arg0: tensor<1x16x16x4xf32>, %arg1: tensor<1x14x14x16xf32>) -> tensor<1x14x14x16xf32> {
    %cst = arith.constant dense_resource<__elided__> : tensor<6x8xf32>
    %cst_0 = arith.constant dense_resource<__elided__> : tensor<8x6xf32>
    %cst_1 = arith.constant 0.000000e+00 : f32
    %0 = tensor.empty() : tensor<8x6xf32>
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c3 = arith.constant 3 : index
    %c16 = arith.constant 16 : index
    %1 = tensor.empty() : tensor<8x8xf32>
    %cst_2 = arith.constant dense_resource<__elided__> : tensor<8x8xf32>
    %cst_3 = arith.constant dense_resource<__elided__> : tensor<8x8xf32>
    %c4 = arith.constant 4 : index
    %cst_4 = arith.constant dense_resource<__elided__> : tensor<64x4x16xf32>
    %2 = tensor.empty() : tensor<8x8x1x3x3x4xf32>
    %3 = scf.for %arg2 = %c0 to %c1 step %c1 iter_args(%arg3 = %2) -> (tensor<8x8x1x3x3x4xf32>) {
      %9 = scf.for %arg4 = %c0 to %c3 step %c1 iter_args(%arg5 = %arg3) -> (tensor<8x8x1x3x3x4xf32>) {
        %10 = affine.apply affine_map<(d0) -> (d0 * 6)>(%arg4)
        %11 = affine.min affine_map<(d0) -> (-d0 + 16, 8)>(%10)
        %12 = scf.for %arg6 = %c0 to %c3 step %c1 iter_args(%arg7 = %arg5) -> (tensor<8x8x1x3x3x4xf32>) {
          %13 = affine.apply affine_map<(d0) -> (d0 * 6)>(%arg6)
          %14 = affine.min affine_map<(d0) -> (-d0 + 16, 8)>(%13)
          %15 = scf.for %arg8 = %c0 to %c4 step %c1 iter_args(%arg9 = %arg7) -> (tensor<8x8x1x3x3x4xf32>) {
            %extracted_slice_5 = tensor.extract_slice %arg0[%arg2, %10, %13, %arg8] [1, %11, %14, 1] [1, 1, 1, 1] : tensor<1x16x16x4xf32> to tensor<?x?xf32>
            %extracted_slice_6 = tensor.extract_slice %arg9[0, 0, %arg2, %arg4, %arg6, %arg8] [8, 8, 1, 1, 1, 1] [1, 1, 1, 1, 1, 1] : tensor<8x8x1x3x3x4xf32> to tensor<8x8xf32>
            %16 = linalg.fill ins(%cst_1 : f32) outs(%1 : tensor<8x8xf32>) -> tensor<8x8xf32>
            %inserted_slice = tensor.insert_slice %extracted_slice_5 into %16[0, 0] [%11, %14] [1, 1] : tensor<?x?xf32> into tensor<8x8xf32>
            %17 = linalg.fill ins(%cst_1 : f32) outs(%extracted_slice_6 : tensor<8x8xf32>) -> tensor<8x8xf32>
            %18 = linalg.matmul ins(%inserted_slice, %cst_3 : tensor<8x8xf32>, tensor<8x8xf32>) outs(%17 : tensor<8x8xf32>) -> tensor<8x8xf32>
            %19 = linalg.matmul ins(%cst_2, %18 : tensor<8x8xf32>, tensor<8x8xf32>) outs(%17 : tensor<8x8xf32>) -> tensor<8x8xf32>
            %inserted_slice_7 = tensor.insert_slice %19 into %arg9[0, 0, %arg2, %arg4, %arg6, %arg8] [8, 8, 1, 1, 1, 1] [1, 1, 1, 1, 1, 1] : tensor<8x8xf32> into tensor<8x8x1x3x3x4xf32>
            scf.yield %inserted_slice_7 : tensor<8x8x1x3x3x4xf32>
          }
          scf.yield %15 : tensor<8x8x1x3x3x4xf32>
        }
        scf.yield %12 : tensor<8x8x1x3x3x4xf32>
      }
      scf.yield %9 : tensor<8x8x1x3x3x4xf32>
    }
    %collapsed = tensor.collapse_shape %3 [[0, 1], [2, 3, 4], [5]] : tensor<8x8x1x3x3x4xf32> into tensor<64x9x4xf32>
    %4 = tensor.empty() : tensor<64x9x16xf32>
    %5 = linalg.fill ins(%cst_1 : f32) outs(%4 : tensor<64x9x16xf32>) -> tensor<64x9x16xf32>
    %6 = linalg.batch_matmul ins(%collapsed, %cst_4 : tensor<64x9x4xf32>, tensor<64x4x16xf32>) outs(%5 : tensor<64x9x16xf32>) -> tensor<64x9x16xf32>
    %expanded = tensor.expand_shape %6 [[0, 1], [2, 3, 4], [5]] : tensor<64x9x16xf32> into tensor<8x8x1x3x3x16xf32>
    %7 = tensor.empty() : tensor<1x18x18x16xf32>
    %8 = scf.for %arg2 = %c0 to %c1 step %c1 iter_args(%arg3 = %7) -> (tensor<1x18x18x16xf32>) {
      %9 = scf.for %arg4 = %c0 to %c3 step %c1 iter_args(%arg5 = %arg3) -> (tensor<1x18x18x16xf32>) {
        %10 = affine.apply affine_map<(d0) -> (d0 * 6)>(%arg4)
        %11 = scf.for %arg6 = %c0 to %c3 step %c1 iter_args(%arg7 = %arg5) -> (tensor<1x18x18x16xf32>) {
          %12 = affine.apply affine_map<(d0) -> (d0 * 6)>(%arg6)
          %13 = scf.for %arg8 = %c0 to %c16 step %c1 iter_args(%arg9 = %arg7) -> (tensor<1x18x18x16xf32>) {
            %extracted_slice_5 = tensor.extract_slice %expanded[0, 0, %arg2, %arg4, %arg6, %arg8] [8, 8, 1, 1, 1, 1] [1, 1, 1, 1, 1, 1] : tensor<8x8x1x3x3x16xf32> to tensor<8x8xf32>
            %extracted_slice_6 = tensor.extract_slice %arg9[%arg2, %10, %12, %arg8] [1, 6, 6, 1] [1, 1, 1, 1] : tensor<1x18x18x16xf32> to tensor<6x6xf32>
            %14 = linalg.fill ins(%cst_1 : f32) outs(%0 : tensor<8x6xf32>) -> tensor<8x6xf32>
            %15 = linalg.matmul ins(%extracted_slice_5, %cst_0 : tensor<8x8xf32>, tensor<8x6xf32>) outs(%14 : tensor<8x6xf32>) -> tensor<8x6xf32>
            %16 = linalg.fill ins(%cst_1 : f32) outs(%extracted_slice_6 : tensor<6x6xf32>) -> tensor<6x6xf32>
            %17 = linalg.matmul ins(%cst, %15 : tensor<6x8xf32>, tensor<8x6xf32>) outs(%16 : tensor<6x6xf32>) -> tensor<6x6xf32>
            %inserted_slice = tensor.insert_slice %17 into %arg9[%arg2, %10, %12, %arg8] [1, 6, 6, 1] [1, 1, 1, 1] : tensor<6x6xf32> into tensor<1x18x18x16xf32>
            scf.yield %inserted_slice : tensor<1x18x18x16xf32>
          }
          scf.yield %13 : tensor<1x18x18x16xf32>
        }
        scf.yield %11 : tensor<1x18x18x16xf32>
      }
      scf.yield %9 : tensor<1x18x18x16xf32>
    }
    %extracted_slice = tensor.extract_slice %8[0, 0, 0, 0] [1, 14, 14, 16] [1, 1, 1, 1] : tensor<1x18x18x16xf32> to tensor<1x14x14x16xf32>
    return %extracted_slice : tensor<1x14x14x16xf32>
  }
}