module {

func.func private @_mlir_ciface_nanoTime() -> i64
func.func private @printI64(i64) -> ()

func.func @matmul(%a: tensor<1024x1024xf32>,  %b: tensor<1024x1024xf32>,  %c: tensor<1024x1024xf32>) -> tensor<1024x1024xf32> {
    %c_out = linalg.matmul ins(%a, %b: tensor<1024x1024xf32>, tensor<1024x1024xf32>) outs(%c: tensor<1024x1024xf32>) -> tensor<1024x1024xf32>
    return %c_out : tensor<1024x1024xf32>
}

func.func @main() {
    %lhs = tensor.empty() : tensor<1024x1024xf32>
    %rhs = tensor.empty() : tensor<1024x1024xf32>
    %dst = tensor.empty() : tensor<1024x1024xf32>
    %start_time = call @_mlir_ciface_nanoTime() : () -> i64
    %dst_0 = call @matmul(%lhs, %rhs, %dst) : (tensor<1024x1024xf32>, tensor<1024x1024xf32>, tensor<1024x1024xf32>) -> tensor<1024x1024xf32>
    %end_time = call @_mlir_ciface_nanoTime() : () -> i64
    %delta = arith.subi %end_time, %start_time : i64
    call @printI64(%delta) : (i64) -> ()
    return
}

}
