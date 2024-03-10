module attributes {torch.debug_module_name = "twoParams"} {
  ml_program.global private mutable @global_seed(dense<0> : tensor<i64>) : tensor<i64>
  func.func @forward(%arg0: tensor<1x3x224x224xf32>) -> tensor<1x1x218x218xf32> {
    %cst = arith.constant dense<[[[[1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00, 0.000000e+00, 1.000000e+00]]]]> : tensor<1x1x5x5xf32>
    %cst_0 = arith.constant dense<[[[[1.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00]], [[0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 1.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00]], [[0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 0.000000e+00], [0.000000e+00, 0.000000e+00, 1.000000e+00]]]]> : tensor<1x3x3x3xf32>
    %cst_1 = arith.constant 0.000000e+00 : f32
    %0 = tensor.empty() : tensor<1x1x222x222xf32>
    %1 = linalg.fill ins(%cst_1 : f32) outs(%0 : tensor<1x1x222x222xf32>) -> tensor<1x1x222x222xf32>
    %2 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%arg0, %cst_0 : tensor<1x3x224x224xf32>, tensor<1x3x3x3xf32>) outs(%1 : tensor<1x1x222x222xf32>) -> tensor<1x1x222x222xf32>
    %3 = tensor.empty() : tensor<1x1x218x218xf32>
    %4 = linalg.fill ins(%cst_1 : f32) outs(%3 : tensor<1x1x218x218xf32>) -> tensor<1x1x218x218xf32>
    %5 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<1> : vector<2xi64>} ins(%2, %cst : tensor<1x1x222x222xf32>, tensor<1x1x5x5xf32>) outs(%4 : tensor<1x1x218x218xf32>) -> tensor<1x1x218x218xf32>
    return %5 : tensor<1x1x218x218xf32>
  }
}
