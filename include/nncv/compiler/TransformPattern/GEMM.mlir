// Transform Patterns.
// !!! MatMul for CPU
//
// Date: Jan 20, 2024

transform.sequence failures(propagate) {
    ^bb0(%arg1: !transform.any_op):
    %matmul_op = transform.structured.match ops{["linalg.matmul"]} in %arg1 : (!transform.any_op) -> !transform.any_op
    %tiled_matmul, %loops:3 = transform.structured.tile_using_for %matmul_op [8, 32, 1] : (!transform.any_op) -> (!transform.any_op, !transform.any_op, !transform.any_op, !transform.any_op)
    // transform.structured.vectorize %tiled_matmul vector_sizes [8, 32, 1] : !transform.any_op
}
