module {

func.func @conv_16433136(%arg0: tensor<1x16x16x4xf32>, %arg2: tensor<1x14x14x16xf32>) -> tensor<1x14x14x16xf32> {
  %c0 = arith.constant dense<0.1> : tensor<3x3x4x16xf32>
  %0 = linalg.conv_2d_nhwc_hwcf {dilations = dense<1> : tensor<2xi64>, strides = dense<1> : tensor<2xi64> }
    ins(%arg0, %c0: tensor<1x16x16x4xf32>, tensor<3x3x4x16xf32>)
    outs(%arg2: tensor<1x14x14x16xf32>) -> tensor<1x14x14x16xf32>
  return %0 : tensor<1x14x14x16xf32>
}
}