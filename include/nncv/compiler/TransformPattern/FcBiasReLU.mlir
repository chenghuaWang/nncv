// Transform Patterns.
// This Pattern is normally used in classification
// 
// pattern: fully connected + Bias + ReLU
//
// Date: Jan 20, 2024

transform.sequence failures(propagate) {
^bb0(%arg0: !transform.any_op,
     %arg1: !transform.op<"linalg.matmul">,
     %arg2: !transform.op<"linalg.elemwise_binary">):
  // The actual tiling transformation takes tile sizes as attributes.
  %loop, %tiled = transform.structured.tile_using_forall %arg1 tile_sizes [4, 32]
    : (!transform.op<"linalg.matmul">) -> (!transform.any_op, !transform.any_op)
  transform.yield
}
