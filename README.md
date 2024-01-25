# NNCV
Neural Networks Inference&Compiling Framework for Computer Vision(NNCV).

**:exclamation::exclamation::exclamation:This is a personal project for practicing purpose:exclamation::exclamation::exclamation:** 


## compiler

## nncv's lang

nncv provides a small programming language called aten-lang(The aten for nncv is different from the aten for torch. :joy: ). It use antlr as its frontend(lexer/parser), mlir/llvm as its backend. nncv defined a `aten dialect` as its high-level IR, and use mlir's downstream dialects as its low-level IR. You can use the command below to run a aten file.

```sh
nncv-c -run example.aten
```

The nncv's compiler will do 3 stages lowering(aten-lang-->aten dialect-->mlir's dialects-->llvm ir) and use LLVM's JIT to execute it. Aten-lang provides a `pfor`(parallel-for) mechanism, which will lowering all `pfor` scope to `affine.for` in mlir. Such as:

```aten
@package = "main";

import "io";

func matmul(lhs Tensor<6, 6, float32>, rhs Tensor<6, 6, float32>, dst Tensor<6, 6, float32>) {
    pfor(/*lower bound, set axis name*/i := 0; /*upper bound*/6; /*step*/ 1) {
        pfor (j := 0; 6; 1) {
            pfor (k := 0; 6; 1) {
                dst[i, j] = dst[i, j] + lhs[i, k] * rhs[k, j]; // do 
            };
        };
    };
};

func main() -> void {
    var lhs Tensor<6, 6, float32>;
    var rhs Tensor<6, 6, float32>;
    var dst Tensor<6, 6, float32>;

    matmul(lhs, rhs, dst);

    io.print(dst);
};
```

nncv will use mlir's native transform dialect to optimize all affine loops. And it also provides some python scripts for creating customized transform file. More examples can be found at [test](./tests/) directory.

Some commands for checking up:

```sh
# The file-suffix is just for noticing the stage. They are all mlir.
# get aten-ir
nncv-c -aten-ir example.aten -o example.air
# get mlir
nncv-c -built-in-mlir exmple.aten -o example.mlir
# get llvm ir
nncv-c -llvm-ir example.mlir -o example.nvm
# run llvm ir
nncv-c -vm example.nvm
```

## highly optimized kernel

```
@software{

}
```