# NNCV
Neural Networks Inference&Compile Framework for Computer Vision(NNCV).

**:exclamation::exclamation::exclamation:This is a personal project for practicing purpose:exclamation::exclamation::exclamation:** 

## compiler

### CPU Target

Currently, nncv supports a very simple lowering pipeline. It basicly uses tiling and vectorization on linalg.ops. However, the vectorization pass is full of bugs, and has performance issues. I'm trying to figure it out, but it takes time.

If you wnat to compile cpu target. U can use commands below to generate a object file:

```sh
nncv-c -warp-c-interface -target HostWoParallel main.mlir -o optimized.mlir
mlir-translate -mlir-to-llvmir optimized.mlir -o main.ll
llc -filetype=object main.ll -o libmain.o
```

### NV GPU Target



## nncv's lang

nncv provides a small programming language called aten-lang(The aten for nncv is different from the aten for torch. :joy: ). It use antlr as its frontend(lexer/parser), mlir/llvm as its backend. nncv defined a `aten dialect` as its high-level IR, and use mlir's downstream dialects as its low-level IR. You can use the command below to run an aten file.

```sh
nncv-c -run example.aten
```

The nncv's compiler will do 3 stages lowering(aten-lang-->aten dialect-->mlir's dialects-->llvm ir) and use LLVM's JIT to execute it. Aten-lang provides a `pfor`(parallel-for) mechanism, which will lowering all `pfor` scopes to `affine.for` in mlir. Such as:

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

after lowering to atenir-mlir, we will get:

```mlir
module @__main {
  Aten.func private @matmul(%arg0: memref<512x512xf32>, %arg1: memref<512x512xf32>, %arg2: memref<512x512xf32>) {
    affine.for %arg3 = 0 to 512 {
      affine.for %arg4 = 0 to 512 {
        affine.for %arg5 = 0 to 512 {
          %0 = memref.load %arg2[%arg3, %arg4] : memref<512x512xf32>
          %1 = memref.load %arg0[%arg3, %arg5] : memref<512x512xf32>
          %2 = memref.load %arg1[%arg5, %arg4] : memref<512x512xf32>
          %3 = Aten.binop(mul, %1, %2) : f32
          %4 = Aten.binop(add, %0, %3) : f32
          memref.store %4, %arg2[%arg3, %arg4] : memref<512x512xf32>
        }
      }
    }
    Aten.return
  }
  Aten.func private @main() {
    %alloc = memref.alloc() : memref<512x512xf32>
    %alloc_0 = memref.alloc() : memref<512x512xf32>
    %alloc_1 = memref.alloc() : memref<512x512xf32>
    Aten.call @matmul(%alloc, %alloc_0, %alloc_1) : (memref<512x512xf32>, memref<512x512xf32>, memref<512x512xf32>) -> ()
    Aten.return
  }
}
```

then lowering all aten-ir to mlir:

```mlir
module @__main {
  func.func private @matmul(%arg0: memref<512x512xf32>, %arg1: memref<512x512xf32>, %arg2: memref<512x512xf32>) {
    affine.for %arg3 = 0 to 512 {
      affine.for %arg4 = 0 to 512 {
        affine.for %arg5 = 0 to 512 {
          %0 = memref.load %arg2[%arg3, %arg4] : memref<512x512xf32>
          %1 = memref.load %arg0[%arg3, %arg5] : memref<512x512xf32>
          %2 = memref.load %arg1[%arg5, %arg4] : memref<512x512xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          memref.store %4, %arg2[%arg3, %arg4] : memref<512x512xf32>
        }
      }
    }
    return
  }
  func.func private @main() {
    %alloc = memref.alloc() : memref<512x512xf32>
    %alloc_0 = memref.alloc() : memref<512x512xf32>
    %alloc_1 = memref.alloc() : memref<512x512xf32>
    call @matmul(%alloc, %alloc_0, %alloc_1) : (memref<512x512xf32>, memref<512x512xf32>, memref<512x512xf32>) -> ()
    return
  }
}
```

nncv will try to use [polymer](https://github.com/kumasento/polymer) to optimize all affine loops. (memref(loadOp, storeOp) will raise to affine if necessary). After optimization, we will get:

```mlir
#map = affine_map<(d0) -> (d0 * 32)>
#map1 = affine_map<(d0) -> (d0 * 32 + 32)>
module @__main {
  func.func private @S0(%arg0: memref<512x512xf32>, %arg1: index, %arg2: index, %arg3: memref<512x512xf32>, %arg4: index, %arg5: memref<512x512xf32>) attributes {scop.stmt} {
    %0 = affine.load %arg0[symbol(%arg1), symbol(%arg2)] : memref<512x512xf32>
    %1 = affine.load %arg5[symbol(%arg1), symbol(%arg4)] : memref<512x512xf32>
    %2 = affine.load %arg3[symbol(%arg4), symbol(%arg2)] : memref<512x512xf32>
    %3 = arith.mulf %1, %2 : f32
    %4 = arith.addf %0, %3 : f32
    affine.store %4, %arg0[symbol(%arg1), symbol(%arg2)] : memref<512x512xf32>
    return
  }
  func.func private @matmul(%arg0: memref<512x512xf32>, %arg1: memref<512x512xf32>, %arg2: memref<512x512xf32>) {
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 16 {
        affine.for %arg5 = 0 to 16 {
          affine.for %arg6 = #map(%arg3) to #map1(%arg3) {
            affine.for %arg7 = #map(%arg5) to #map1(%arg5) {
              affine.for %arg8 = #map(%arg4) to #map1(%arg4) {
                func.call @S0(%arg2, %arg6, %arg8, %arg1, %arg7, %arg0) : (memref<512x512xf32>, index, index, memref<512x512xf32>, index, memref<512x512xf32>) -> ()
              }
            }
          }
        }
      }
    }
    return
  }
  func.func private @main() {
    %alloc = memref.alloc() : memref<512x512xf32>
    %alloc_0 = memref.alloc() : memref<512x512xf32>
    %alloc_1 = memref.alloc() : memref<512x512xf32>
    call @matmul(%alloc, %alloc_0, %alloc_1) : (memref<512x512xf32>, memref<512x512xf32>, memref<512x512xf32>) -> ()
    memref.dealloc %alloc_1 : memref<512x512xf32>
    memref.dealloc %alloc_0 : memref<512x512xf32>
    memref.dealloc %alloc : memref<512x512xf32>
    return
  }
}
```

Finally, nncv's lowering pipeline will lowering mlir to llvm ir. More examples can be found at [test](./tests/) directory.

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