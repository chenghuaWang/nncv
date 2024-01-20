module {
    func.func @testMatMulDefault(%lhs: tensor<720x720xf32>, %rhs: tensor<720x720xf32>, %dst: tensor<720x720xf32>) -> tensor<720x720xf32>{
        %res = linalg.matmul 
                ins(%lhs, %rhs : tensor<720x720xf32>, tensor<720x720xf32>) 
                outs(%dst : tensor<720x720xf32>) -> tensor<720x720xf32>
        func.return %res : tensor<720x720xf32> 
    }
}