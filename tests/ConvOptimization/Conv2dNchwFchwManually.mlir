module {


func.func private @_mlir_ciface_nanoTime() -> i64
func.func private @printI64(i64) -> ()

func.func @batch_nchw_conv(%arg0: tensor<1x3x262x262xf32>, %arg1: tensor<64x3x7x7xf32>, %arg2: tensor<1x64x128x128xf32>) -> tensor<1x64x128x128xf32> {
    // res18 1st conv
    %2 = linalg.conv_2d_nchw_fchw {dilations = dense<1> : vector<2xi64>, strides = dense<2> : vector<2xi64>}
        ins(%arg0, %arg1 : tensor<1x3x262x262xf32>, tensor<64x3x7x7xf32>)
        outs(%arg2 : tensor<1x64x128x128xf32>) -> tensor<1x64x128x128xf32>
    return %2 : tensor<1x64x128x128xf32>
}

func.func @main() {
    %in = tensor.empty() : tensor<1x3x262x262xf32>
    %kernel = tensor.empty() : tensor<64x3x7x7xf32>
    %out = tensor.empty() : tensor<1x64x128x128xf32>
    %start_time = call @_mlir_ciface_nanoTime() : () -> i64
    %dst_0 = call @batch_nchw_conv(%in, %kernel, %out) : (tensor<1x3x262x262xf32>, tensor<64x3x7x7xf32>, tensor<1x64x128x128xf32>) -> tensor<1x64x128x128xf32>
    %end_time = call @_mlir_ciface_nanoTime() : () -> i64
    %delta = arith.subi %end_time, %start_time : i64
    call @printI64(%delta) : (i64) -> ()
    func.return
}
}