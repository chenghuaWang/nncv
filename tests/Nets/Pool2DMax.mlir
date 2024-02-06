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


// scf.for %arg1 = %c0 to %c1 step %c1 {
//   scf.for %arg2 = %c0 to %c3 step %c1 {
//     scf.for %arg3 = %c0 to %c74 step %c1 {
//       scf.for %arg4 = %c0 to %c74 step %c1 {
//         scf.for %arg5 = %c0 to %c3 step %c1 {
//           scf.for %arg6 = %c0 to %c3 step %c1 {
//             %2 = affine.apply #map(%arg3, %arg5)
//             %3 = affine.apply #map(%arg4, %arg6)
//             %4 = memref.load %0[%arg1, %arg2, %2, %3] : memref<1x3x224x224xf32, strided<[?, ?, ?, ?], offset: ?>>
//             %5 = memref.load %alloc[%arg1, %arg2, %arg3, %arg4] : memref<1x3x74x74xf32>
//             %6 = arith.maximumf %5, %4 : f32
//             memref.store %6, %alloc[%arg1, %arg2, %arg3, %arg4] : memref<1x3x74x74xf32>
//           }
//         }
//       }
//     }
//   }
// }