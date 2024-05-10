# NNCV
Neural Networks Inference&Compile Framework for Computer Vision(NNCV).

**:exclamation::exclamation::exclamation:This is a personal project for practicing purpose:exclamation::exclamation::exclamation:** 

- [1. Compiler](#1-compiler)
  - [1.1 CPU Target](#11-cpu-target)
  - [1.2 NV GPU Target](#12-nv-gpu-target)
  - [1.3 Using external model parameters](#13-using-external-model-parameters)
  - [1.4 Binary Params Data Layout](#14-binary-params-data-layout)
- [2. Nncv's Lang](#2-nncvs-lang)
  - [2.1 Examples](#21-examples)
    - [2.1.1 Quick Pow](#211-quick-pow)
    - [2.1.2 Quick Sort](#212-quick-sort)
    - [2.1.3 Call External Libraries](#213-call-external-libraries)
  - [2.2 Parallel For Loops](#22-parallel-for-loops-in-nncvs-lang)
- [Cite](#cite)


## 1. Compiler

Before starting to compile, you need to get the mlir file for a torch model using [torch-mlir](https://github.com/llvm/torch-mlir) tool. example:


```python
import torch
import torchvision
import torch_mlir

def run():
    net = torchvision.models.resnet18(weights=torchvision.models.ResNet18_Weights.DEFAULT)
    #net = net.to(memory_format=torch.channels_last)
    a = torch.zeros([1, 3, 256, 256])
    #a = a.to(memory_format=torch.channels_last)
    a = a.half()
    net.train(False)
    net.half()
    module = torch_mlir.compile(net, a, output_type="linalg-on-tensors")
    with open("res18-half.mlir", "wb") as f:
        #f.write(module.operation.get_asm(large_elements_limit=0).encode())
        f.write(module.operation.get_asm().encode())

if __name__ == "__main__":
    run()
```


The torch-mlir converted file puts the model parameters in the mlir file as well, which is not conducive to model parameter updates and makes the file to be compiled extremely large.

nncv provides a `-split-params` option to split model parameters and behavior. It traverses the memref.global operator in the mlir file and saves the dense attribute inside a binary file. For the original function, e.g.: `func.func(in)->out`, nncv will turn it into `func.func(in, params)->out`.

### 1.1. CPU Target

Currently, nncv supports a very simple lowering pipeline. It basicly uses tiling and vectorization on linalg.ops. And this vectorization method currently only supports CPUs with the AVX2 feature.

If you want to compile a DL model to cpu target(without parallel). You can use commands below to generate a object file:

```sh
nncv-c -wrap-c-interface -target HostWoParallel res18.mlir -o optimizedRes18.mlir
mlir-translate -mlir-to-llvmir optimizedRes18.mlir -o res18.ll
llc -filetype=object res18.ll -o libres18.o
```

> If you want to enable multi-threads on cpu target, use `HostWParallel` option instead:
>
> `nncv-c -wrap-c-interface -target HostWParallel res18.mlir -o optimizedRes18.mlir`

At this point, you can write a simple piece of code to call the forward function inside libres18.o. Here I give a simple C++ implementation.

```c++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <chrono>
using namespace std::chrono;

#define B 1
#define C 3
#define H 256
#define W 256

template <typename T, size_t N> struct MemRefDescriptor {
  T *allocated;
  T *aligned;
  intptr_t offset;
  intptr_t sizes[N];
  intptr_t strides[N];
};

extern "C" {
void _mlir_ciface_forward(MemRefDescriptor<float, 2>* dst, MemRefDescriptor<float, 4>* src);
}

int main(){
  float *_dst_data_ptr = (float*)malloc(sizeof(float) * (long long)1 * 1000);
  float *_src_data_ptr = (float*)malloc(sizeof(float) * (long long)B * C * H * W);

  MemRefDescriptor<float, 2> dst = {
    _dst_data_ptr,    // allocated
    _dst_data_ptr,    // aligned
    0,    // offset
    {1, 1000}, // sizes[N]
    {1000, 1},  // strides[N]
  };

  MemRefDescriptor<float, 4> src = {
    _src_data_ptr,    // allocated
    _src_data_ptr,    // aligned
    0,    // offset
    {B, C, H, W}, // sizes[N]
    {C * H * W, H * W, H, 1},  // strides[N]
  };

  auto startTime = system_clock::now();
  _mlir_ciface_forward(&dst, &src);
  auto endTime = system_clock::now();

  auto tt = duration_cast<milliseconds>(endTime - startTime);

  std::cout << "Time: " << tt.count() << "ms" << std::endl;

  free(_dst_data_ptr);
  free(_src_data_ptr);

  return 0;
}
```

An executable file can be generated using the following compilation instructions

```sh
clang++ -O3 -Wall libres18.o RunResNet18.cpp -L{MLIR_LIB_DIR} -lmlir_runner_utils -lmlir_c_runner_utils -lm && ./a.out
# if using openmp
clang++ -O3 -Wall libres18.o RunResNet18.cpp -L{MLIR_LIB_DIR} -lmlir_runner_utils -lmlir_c_runner_utils -lm -lomp && ./a.out
```

### 1.2 NV GPU Target

nncv will try to use wmma intr provided by Tensor Core. Tensor Core supports tf32 type, which is quite different from fp32. For simpilify, if you want to lowering a model to NV Gpu tagret, half precision(fp16) is adopted by default.

### 1.3 Using external model parameters

If you want to use external model parameters, then you need to import an nncv runtime library.

```c++
#include "libnncv/DataType.hpp"
#include "libnncv/SystemIo.hpp"

using namespace nncv::rt;

MemRefFlatArray params(dataType::kFloat32);
params.read("model.bin")

_mlir_ciface_forward(..., ..., params.get());
```

### 1.4 Binary Params Data Layout

```txt
+---------------------+
|      MemRefHead     |
| int64_t Magic Number|
| size_t  Offset      |
| size_t Nums Indexer |
+---------------------+
|     Indexer-1       |
| char[128] Name      |
| size_t Dims         |
| size_t[8] Shape     |
| size_t EleWidth     |
| size_t Aligned      |
| size_t Offset       |
+---------------------+
|     Indexer-2       |
+---------------------+
|     Indexer-3       |
+---------------------+
|     Indexer-4       |
+---------------------+
|       data-1        |
+---------------------+
|       data-2        |
+---------------------+
|       data-3        |
+---------------------+
```

## 2. Nncv's Lang

nncv provides a small programming language called aten-lang(The aten for nncv is different from the aten for torch. :joy: ). It use antlr as its frontend(lexer/parser), mlir/llvm as its backend. nncv defined a `aten dialect` as its high-level IR, and use mlir's downstream dialects as its low-level IR. You can use the command below to run an aten file.

```sh
nncv-c -run example.aten
```

If you want to enable multi thread support and eanble polymer, use:

```sh
nncv-c -womp -wpoly -run example.aten
```

The nncv's compiler will do 3 stages lowering(aten-lang-->aten dialect-->mlir's dialects-->llvm ir) and use LLVM's JIT to execute it. 

### 2.1 Examples

#### 2.1.1 Quick Pow

<details>
<summary>[Quick Pow in nncv's lang(click to expand)]</summary>

```aten
@package = "main";

import "io";

func QuickPow(a int32, n int32) -> int32 {
  res := 0;
  if (n == 0) {
    res = 1;
  } else if (n%2 == 1) {
    res = QuickPow(a, n-1) * a;
  } else {
    temp := QuickPow(a, n/2);
    res = temp * temp;
  };
  return res;
};

func main() {
  res := QuickPow(2, 10);
  io.print(res);
};
```
</details>

#### 2.1.2 Quick Sort

<details>
<summary>[Quick Sort in nncv's lang(click to expand)]</summary>

```aten
@package = "main";

import "io";

func _partion(A Tensor<6, int32>, low int32, high int32) -> int32 {
    low_t := low; high_t := high; pivot := A[low_t];
    while(low_t < high_t) {
        while(low_t < high_t && A[high_t] >= pivot) {high_t--;};
        A[low_t] = A[high_t];
        while(low_t < high_t && A[low_t] <= pivot) {low_t++;};
        A[high_t] = A[low_t];
    };
    A[low_t] = pivot;
    return low_t;
};

func QuickSort(A Tensor<6, int32>, low int32, high int32) {
    if (low < high) {
        pivotPos := _partion(A, low, high);
        QuickSort(A, low, pivotPos-1);
        QuickSort(A, pivotPos+1, high);
    };
};

func main() {
    var array Tensor<6, int32>;
    for(i:=0; i < 6; i++) {
        array[i] = 6 - i;
    };
    io.print(array);
    QuickSort(array, 0, 5);
    io.print(array);
};
```

</details>

#### 2.1.3 Call External Libraries

<details>
<summary>[Call External Libraries in nncv's lang(click to expand)]</summary>

```aten
@package = "main";

func _lib_nncv_do_something(Tensor<1, 1, float32>);

pub func add(a int32, b int32) -> int32 {
    return a + b;
};

func main() {
    res := add(8, 8);
    var t Tensor<1, 1, float32>;
    _lib_nncv_do_something(t);
};
```

</details>


#### 2.1.3 Conv2d 3x3

<details>
<summary>[Conv2d 3x3 in nncv's lang(click to expand)]</summary>

```aten
@package = "main";

import "io";

func Conv2d(input Tensor<1, 3, 2048, 2048, float32>,
            kernel Tensor<16, 3, 3, 3, float32>,
            output Tensor<1, 16, 2046, 2046, float32>) {
    pfor (n := 0; 1; 1) {
        pfor (k := 0; 16; 1) {
            pfor (oh := 0; 2046; 1) {
                pfor (ow := 0; 2046; 1) {
                    pfor (c := 0; 3; 1) {
                        pfor (r := 0; 3; 1) {
                            pfor (s := 0; 3; 1) {
                                output[n, k, oh, ow] = output[n, k, oh, ow] + input[n, c, oh + r, ow + s] * kernel[k, c, r, s];
                            };
                        };
                    };
                };
            };
        };
    };
};

func main() {
    // NCHW
    var input Tensor<1, 3, 2048, 2048, float32>;
    // KCRS
    var kernel Tensor<16, 3, 3, 3, float32>;
    // padding = 0, stride = 1
    var output Tensor<1, 16, 2046, 2046, float32>;

    // timing.
    start := io.clock();
    Conv2d(input, kernel, output);
    end := io.clock();
    io.print(end - start);
    io.newLine();
};
```

</details>

### 2.2 Parallel For Loops

Aten-lang provides a `pfor`(parallel-for) mechanism, which will lowering all `pfor` scopes to `affine.for` in mlir. Such as:

```aten
@package = "main";

import "io";

func matmul(lhs Tensor<512, 512, float32>, rhs Tensor<512, 512, float32>, dst Tensor<512, 512, float32>) {
    pfor(/*lower bound, set axis name*/i := 0; /*upper bound*/6; /*step*/ 1) {
        pfor (j := 0; 6; 1) {
            pfor (k := 0; 6; 1) {
                dst[i, j] = dst[i, j] + lhs[i, k] * rhs[k, j]; // do 
            };
        };
    };
};

func main() -> void {
    var lhs Tensor<512, 512, float32>;
    var rhs Tensor<512, 512, float32>;
    var dst Tensor<512, 512, float32>;

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

## Cite

```
@software{

}
```