// test conv_2d_nchw_fchw using manually vectorization.

module {
func.func @batch_nchw_conv(%arg0: tensor<1x3x262x262xf32>, %arg1: tensor<64x3x7x7xf32>, %arg2: tensor<1x64x128x128xf32>) -> tensor<1x64x128x128xf32> {
    // res18 1st conv
    %2 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>} 
        ins(%arg0, %arg1 : tensor<1x3x262x262xf32>, tensor<64x3x7x7xf32>) 
        outs(%arg2 : tensor<1x64x128x128xf32>) -> tensor<1x64x128x128xf32>
    return %2 : tensor<1x64x128x128xf32>
}

// func.func @conv_2d_nchw_fchw(%arg0: memref<?x?x?x?xf32>, %arg1: memref<?x?x?x?xf32>, %arg2: memref<?x?x?x?xf32>) {
//     linalg.conv_2d_nchw_fchw ins(%arg0, %arg1 : memref<?x?x?x?xf32>, memref<?x?x?x?xf32>) outs(%arg2 : memref<?x?x?x?xf32>)
//     return
// }
}