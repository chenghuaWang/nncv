// Linalg Operation Set for NNCV
//
// WARNING: It's depends if I really need this lib. Actually, use MLIR
// Tool Chain when lowring .aten files is ok. But that means I need to
// maintain a hard coded linalg func -> tensor opset table.
// linalg_opset.mlir Aug 12, 2023. V0.0.1
//
// chenghua.wang.edu@gmail.com
//
// This file works as an external link library. All functions is written in
// `func`, `scf`, `tensor`, `linalg` and other build in Op provided by mlir. 
// And it will be build to a dynamic library.
//
// This lib is an import when needed lib, user should use scentence `import nn`
// to include this external lib.
module {

}