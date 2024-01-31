module {

func.func private @_mlir_ciface_nanoTime() -> i64
func.func private @printI64(i64) -> ()

func.func @matmul(%a: tensor<129x256xf32>,  %b: tensor<256x64xf32>,  %c: tensor<129x64xf32>) -> tensor<129x64xf32> {
    %c_out = linalg.matmul ins(%a, %b: tensor<129x256xf32>, tensor<256x64xf32>) outs(%c: tensor<129x64xf32>) -> tensor<129x64xf32>
    return %c_out : tensor<129x64xf32>
}

func.func @main() {
    %lhs = tensor.empty() : tensor<129x256xf32>
    %rhs = tensor.empty() : tensor<256x64xf32>
    %dst = tensor.empty() : tensor<129x64xf32>
    %start_time = call @_mlir_ciface_nanoTime() : () -> i64
    %dst_0 = call @matmul(%lhs, %rhs, %dst) : (tensor<129x256xf32>, tensor<256x64xf32>, tensor<129x64xf32>) -> tensor<129x64xf32>
    %end_time = call @_mlir_ciface_nanoTime() : () -> i64
    %delta = arith.subi %end_time, %start_time : i64
    call @printI64(%delta) : (i64) -> ()
    return
}

}