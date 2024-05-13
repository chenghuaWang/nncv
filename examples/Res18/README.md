# How to compile Res18 and link it to your program

## Compile Res18
### export mlir using torch-mlir

```python
import torch
import torchvision
import torch_mlir

def run():
    net = torchvision.models.resnet18(weights=torchvision.models.ResNet18_Weights.DEFAULT)
    a = torch.zeros([1, 3, 256, 256])
    net.train(False)
    module = torch_mlir.compile(net, a, output_type="linalg-on-tensors")
    with open("res18.mlir", "wb") as f:
        f.write(module.operation.get_asm().encode())
```

### compile using NNCV

```shell
nncv-c --target HostWParallel --split-params --wrap-c-interface res.mlir -o /optimized/res.mlir
```

### get the object file using llvm toolchain

```shell
mlir-translate -mlir-to-llvmir res.mlir -o res18.ll
llc -filetype=obj res18.ll -o libres18.o
```

## Write a driver function

see `main.cpp` in this directory

## Compile it using clang++

```shell
clang++ main.cpp libres18.o -no-pie -O3 -lmlir_runner_utils -lmlir_c_runner_utils -lomp -L. -lnncv_rt -I./third_party/stb_image
```