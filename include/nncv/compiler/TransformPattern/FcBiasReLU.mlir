// Transform Patterns.
// This Pattern is normally used in classification
// 
// pattern: fully connected + Bias + ReLU
//
// Date: Jan 20, 2024

module attributes { transform.with_named_sequence } {
    transform.named_sequence @__transform_main(%arg1: !transform.any_op {transform.readonly}, %arg2: !transform.any_op {transform.readonly}) {
        // match op 1: linalg.matmul
        %0 = transform.structured.match ops{["linalg.matmul"]} in %arg1 : (!transform.any_op) -> !transform.any_op
        // match op 2: linalg.elemwise_binary
        %1 = transform.structured.match ops{["linalg.elemwise_binary"]} in %arg2 : (!transform.any_op) -> !transform.any_op
        
        // then
        
        transform.yield
    }
}
