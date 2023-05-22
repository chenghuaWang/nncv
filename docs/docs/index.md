# NNCV

NNCV(**N**eural **N**etwork Inference and Compile Tool Chain for **C**omputer **V**ision) is a tool chain designed to accelerate deep learning networks(especially operators for computer vision) using compile techniques. **It's a personal project for practicing purpose. This may be a good example for learning MLSys, but it is certainly not the optimal framework for production environments.**

## Topics we will cover

1. Compile Techniques:
    * A simple Lexer and Parser(using Nested case statement)
    * Multi Level Intermediate Representation(MLIR)
        * Dialects
        * Convert
        * Lowering
        * Some specific optimization tips(op-fusion, etc)
        * CodeGen
    * Polyhedral Compilation Technology

2. Auto Parallel
    * Polyhedral Compilation Technology
    * Affine in MLIR

3. CUDA Programming
    * Kernel impl(Mul, GEMM, Conv(img2col, winograd), etc)

4. Virtual Machine Design

## Features

# Arch

# Third party packages' dependencies

* LLVM(mostly MLIR)
* stb image
* OpenCV

# Build and Install

# Routine

|               Contents                |     Date     |   State    |
| :-----------------------------------: | :----------: | :--------: |
|     Lexer of Auto Tensor Language     | May 22, 2023 | On working |
| Pre-processor of Auto Tensor Language | May 22, 2023 | On working |

# Citing

```
@software {nncv,
    author = {chenghua.Wang},
    title = {NNCV: Neural Network Inference and Compile Tool Chain for Computer Vision},
    url = {https://chenghuawang.github.io/nncv/},
    version = {0.1.2},
    date = {2024-01-01},
}
```

# Contribute to this project