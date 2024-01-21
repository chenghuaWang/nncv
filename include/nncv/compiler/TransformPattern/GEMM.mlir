// Transform Patterns.
// !!! MatMul for CPU
//
// Date: Jan 20, 2024

module attributes { transform.with_named_sequence } {
    transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}) {
        // match op: linalg.matmul
        %0 = transform.structured.match ops{["linalg.matmul"]} in %arg1 : (!transform.any_op) -> !transform.any_op

        // Judging to use GEMM or GEMV
        
        // then
        %1:2 = transform.structured.tile_using_forall %0 num_threads [10, 20] (mapping = [ #gpu.thread<y>, #gpu.thread<x> ] )
           : (!transform.any_op) -> (!transform.any_op, !transform.any_op)

        transform.yield
    }
}