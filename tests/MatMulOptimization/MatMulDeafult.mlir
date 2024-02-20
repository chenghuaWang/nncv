module {

func.func @matmul(%a: tensor<512x1024xf32>,  %b: tensor<1024x512xf32>,  %c: tensor<512x512xf32>) -> tensor<512x512xf32> {
    %c_out = linalg.matmul ins(%a, %b: tensor<512x1024xf32>, tensor<1024x512xf32>) outs(%c: tensor<512x512xf32>) -> tensor<512x512xf32>
    return %c_out : tensor<512x512xf32>
}

func.func @mymain() {
    %lhs = tensor.empty() : tensor<512x1024xf32>
    %rhs = tensor.empty() : tensor<1024x512xf32>
    %dst = tensor.empty() : tensor<512x512xf32>
    
    %dst_0 = call @matmul(%lhs, %rhs, %dst) : (tensor<512x1024xf32>, tensor<1024x512xf32>, tensor<512x512xf32>) -> tensor<512x512xf32>
    return
}

}