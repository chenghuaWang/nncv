AutoTensor is a very simple and easy to use programming language. You can use neted for loop to implement your logic and leave everything else to the compiler!!! The compiler will do the parallelization automatically for you!!!

## Grammar and Features

```
import "nn"
# "nn" is not a file, this import works like a Compile Flag.
# The Preprocessor will replace `import "nn"` with
# `@Compiler.Ops.Extension.Enable`

import "std"
# Same as Compile Command `@Compiler.Std.Enable`

import "io.aten"
# import "std" will set `@Compiler.Io.Enable`
# "io.aten" is a warpper of buildin "io" primitives.

# If you want to import files, the method shown below is recommended:
# import "foo.aten"
# import "nncv/api/autoTensor/core.aten"

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

struct MyOp {
    Tensor *c;
}

# `&self` will be translate to `MyOp*`
impl MyOp {
    # Constructor
    # This `new` function will return a class but without
    # memory copy(using shallow copy).
    # --
    # If user use `std.Alloc(MyOp<args...>)` to create this class, `std.Alloc`
    # will call new(...).
    func new() -> MyOp {
        MyOp ret;
        ret.c = std.Alloc(Tensor<100, 100, int16>);
        return ret;
    }

    # deconstructor
    func delete(&self) -> void {
        # delete will be called when this function exists
    }

    # overload a operator
    func __equal__(&self, MyOp* _rhs) -> bool {
        return (*self.c) == (*_rhs.c)
    }

    # user defind method
    func Mul(&self, Tensor* _rhs, Tensor* _to) -> void {
        Gemm2D(self.c, _rhs, _to);
    }
}

func main() {
    # <> is constructor of all Types!!! Not template.
    Tensor a<100, 100, float32>;
    Tensor b<100, 100, float32>;
    Tensor c<100, 100, float32>;
    var start_time = std.Time()
    Gemm2D(&a, &b, &c);
    var end_time = std.Time();
    std.Print('Time usage: ', std.TimeAsMliSec(start_time - end_time), '\n');
    std.Print(c);

    # Tensor* c = std.Alloc(Tensor<100, 100, 100, int16>);
    # std.Free(c);
    # c = null;
    # Tensor* d = std.Clone(c);

    # MyOp o = MyOp.new();  # This value will auto delete.
    # o = MyOp<>;  # This scentence is same as MyOp.new()
    # MyOp* foo = std.Alloc(MyOp<args...>);  # The pointer should free by user.
}
```

### Buildin Ops

I implemented lots of buildin Ops in compiler level. And thoes Ops is shared same impl with NNCV-IR. Actually, the Auto Tensor-lang's IR will convert to NNCV-IR. And NNCV-IR will finally lowering to Affine-IR, Linag-IR, etc. 

> **Before starting to use these Ops:** You should import "nn.aten", "nn.aten" is just a flag that tell compiler to use extented Op set.

The Ops supported is briefly shown below:

|    Op Name     |    Describe    |
| :------------: | :------------: |
| nn.Conv2d(...) | 2d convolution |

---

For the full list of Op that supported, Check the [AutoTen-lang Ops' Support Chapter](AutoTensor-Ops-Supported.md)

## Preprocessor

## Lexer

AutoTen-lang is not strictly follow $\text{LL(1)}$(It has `*` for multiplication and pointer).

## Parser

## Dialects Design

## Reference

* Programming Language Pragmatics 4th
* [LLVM Pascal Scanner](https://github.com/FrozenGene/LLVMPascalCompiler/blob/master/LLVMPascal/LLVMPascal/scanner.cpp#L172)
* [How to learn AI Compiler](https://www.zhihu.com/question/564620976/answer/2848127300)
