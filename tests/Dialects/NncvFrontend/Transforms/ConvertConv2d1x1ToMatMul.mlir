func.func @conv() -> tensor<1x2x2x4xf32> {
  %cst = arith.constant 0.000000e+00 : f32
  %0 = tensor.empty() : tensor<1x2x2x3xf32>
  %1 = tensor.empty() : tensor<1x1x3x4xf32>
  %2 = tensor.empty() : tensor<1x2x2x4xf32>
  %3 = linalg.fill ins(%cst : f32) outs(%2 : tensor<1x2x2x4xf32>) -> tensor<1x2x2x4xf32>
  %4 = linalg.conv_2d_nhwc_hwcf {dilations = dense<1> : tensor<2xi64>, strides = dense<1> : tensor<2xi64>} ins(%0, %1 : tensor<1x2x2x3xf32>, tensor<1x1x3x4xf32>) outs(%3 : tensor<1x2x2x4xf32>) -> tensor<1x2x2x4xf32>
  return %4 : tensor<1x2x2x4xf32>
}
// %4 = linalg.conv_2d_nhwc_hwcf {dilations = dense<1> : tensor<2xi64>, strides = dense<1> : tensor<2xi64>} ins(%0, %1 : tensor<1x2x2x3xf32>, tensor<1x1x3x4xf32>) outs(%3 : tensor<1x2x2x4xf32>) -> tensor<1x2x2x4xf32>
// Should be transformed to code below:
// %4 = tensor.collapse_shape %0 [[0, 1, 2], [3]] : tensor<1x2x2x3xf32> into tensor<4x3xf32>
// %5 = tensor.collapse_shape %1 [[0, 1, 2], [3]] : tensor<1x1x3x4xf32> into tensor<3x4xf32>
// %6 = tensor.collapse_shape %3 [[0, 1, 2], [3]] : tensor<1x2x2x4xf32> into tensor<4x4xf32>
// %7 = linalg.matmul ins(%4, %5 : tensor<4x3xf32>, tensor<3x4xf32>) outs(%6 : tensor<4x4xf32>) -> tensor<4x4xf32>
// %8 = tensor.expand_shape %7 [[0, 1, 2], [3]] : tensor<4x4xf32> into tensor<1x2x2x4xf32>