// Tensor Operation Set for NNCV
// tensor_opset.mlir Aug 12, 2023. V0.0.1
//
// WARNING: It's depends if I really need this lib. Actually, use MLIR
// Tool Chain when lowring .aten files is ok. But that means I need to
// maintain a hard coded tensor func -> tensor opset table.
//
// chenghua.wang.edu@gmail.com
//
// This file works as an external link library. All functions is written in
// `func`, `scf`, `tensor` and other build in Op provided by mlir. And it will
// be build to a dynamic library.
//
// This lib is a builtin lib, user do not need to use scentence `import tensor_opset`
// nncv-vm will link this lib before run `_exec_main()` program entrance.

module {
//===----------------------------------------------------------------------===//
// runtime tensor index op.
//
// Symbol Name: __rt_tensor_index
// Args: 
//===----------------------------------------------------------------------===//
func.func public @__rt_tensor_opset_index() -> f32 {
    %1 = arith.constant 42.0 : f32
    return %1 : f32
}


}

