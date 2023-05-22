AutoTen
---

# Grammar and Features

```
import "nn.aten"

@Kernel.AutoParallel
func Gemm2D(Tensor* _src_1, Tensor* _src_2, Tensor* _dst) -> bool {
    int w = _src_1.shape[1];
    int h = _src_1.shape[2];

    for (int i = 0; i < w; i++) {
        # do something.
        _src_1[1, 1]; # python-like indexing.
    }

    return false;
}

func main() {
    Tensor a<100, 100, float32>;
    Tensor b<100, 100, float32>;
    Tensor c<100, 100, float32>;
    Gemm2D(&a, &b, &c);
    Print(c);
}
```

## Buildin Ops

I implemented lots of buildin Ops in compiler level. And thoes Ops is shared same impl with NNCV-IR. Actually, the Auto Tensor-lang's IR will convert to NNCV-IR. And NNCV-IR will finally lowering to Affine-IR, Linag-IR, etc. 

> **Before starting to use these Ops:** You should import "nn.aten", "nn.aten" is just a flag that tell compiler to use extented Op set.

The Ops supported is briefly shown below:

|Op Name|Describe|
|:-:|:-:|
|nn.Conv2d(...)|2d convolution|

---

For the full list of Op that supported, Check the [AutoTen-lang Ops' Support Chapter](AutoTensor-Ops-Supported.md)

# Preprocessor

# Lexer

# Parser

# Dialects Design

# Reference

* Programming Language Pragmatics 4th
* [LLVM Pascal Scanner](https://github.com/FrozenGene/LLVMPascalCompiler/blob/master/LLVMPascal/LLVMPascal/scanner.cpp#L172)
