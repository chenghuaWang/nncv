module {
    func.func @testMatMulDefault(%lhs: memref<720x720xf32>, %rhs: memref<720x720xf32>, %dst: memref<720x720xf32>) {
        linalg.matmul 
                ins(%lhs, %rhs : memref<720x720xf32>, memref<720x720xf32>) 
                outs(%dst : memref<720x720xf32>)
        func.return
    }
}