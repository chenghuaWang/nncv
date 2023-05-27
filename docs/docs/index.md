[English](./index.md) | [简体中文](./zh-cn/index.md)

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

## Contents of NNCV Docs

* [Preface: Introduction of NNCV](./index.md)
* [Chapter 1: Overview of NNCV's Architecture]()
* [Chapter 2: Auto Tensor Language](./AutoTensor-Lang.md)
    * [2.1: Grammar in details](./AutoTensor-Grammar.md)
    * [2.2: The front-end implementation]()
    * [2.3: Optimizations]()
        * [2.3.1: MLIR Based Backend]()
        * [2.3.2: Auto parallelism]()
    * [2.A: Operators Auto Tensor now supported](./AutoTensor-Ops-Supported.md)
    * [2.B: Compile Flags Check Table]()
    * [2.C: Extent Libraris Check Table]()
* [Chapter 3: The NNCV IR]()
* [Chapter 4: Code Generation and Execution]()
    * [4.1: LLVM IR, SPIR-V IR and GPU IR]()
    * [4.2: AOT and JIT]()
    * [4.3: Using Virtual Machine]()
* [Chapter 5: The NNCV's Virtual Machine]()
    * [5.1: Bytecode and Instruction Design]()
    * [5.2: Kernel as plugin]()
    * [5.3: Scheduling]()
* [Chapter 6: Inference using TorchScript and ONNX]()
    * [6.1: Convert from TorchScript IR to NNCV IR]()
    * [6.2: Convert from ONNX IR to NNCV IR]()
* [Chapter 7: Experiments]()
    * [7.1: Auto Parallelism]()
        * [7.1.1: On CPU(x86)]()
        * [7.1.2: On CUDA Device]()
        * [7.1.3: Using Graphic Pipeline]()
    * [7.2: Inference on Single Node]()
    * [7.3: Multi-Node Scheduling]()
* [Chapter 8: Builtin Kernel Optimization]()
    * [8.1: Convolution]()
    * [8.2: GEMM]()
    * [8.3: Pooling]()

## Features

## Arch

## Third party packages' dependencies

* LLVM(mostly MLIR)
* stb image
* OpenCV

## Build and Install

## Routine

|               Contents                |     Date     |   State    |
| :-----------------------------------: | :----------: | :--------: |
|     Lexer of Auto Tensor Language     | May 22, 2023 | On working |
| Pre-processor of Auto Tensor Language | May 22, 2023 | On working |

## Citing

```
@software {nncv,
    author = {chenghua.Wang},
    title = {NNCV: Neural Network Inference and Compile Tool Chain for Computer Vision},
    url = {https://chenghuawang.github.io/nncv/},
    version = {0.1.2},
    date = {2024-01-01},
}
```

## Contribute to this project
