module attributes {torch.debug_module_name = "net_pool2d_max"} {
  ml_program.global private mutable @global_seed(dense<0> : tensor<i64>) : tensor<i64>
  func.func @forward(%arg0: tensor<1x3x224x224xf32>) -> tensor<1x3x74x74xf32> {
    %cst = arith.constant 0xFF800000 : f32
    %0 = tensor.empty() : tensor<1x3x74x74xf32>
    %1 = linalg.fill ins(%cst : f32) outs(%0 : tensor<1x3x74x74xf32>) -> tensor<1x3x74x74xf32>
    %2 = tensor.empty() : tensor<3x3xf32>
    %3 = linalg.pooling_nchw_max {dilations = dense<1> : vector<2xi64>, strides = dense<3> : vector<2xi64>} ins(%arg0, %2 : tensor<1x3x224x224xf32>, tensor<3x3xf32>) outs(%1 : tensor<1x3x74x74xf32>) -> tensor<1x3x74x74xf32>
    return %3 : tensor<1x3x74x74xf32>
  }
}
