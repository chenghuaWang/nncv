#ifndef NNCV_LINALGEXT_OPS
#define NNCV_LINALGEXT_OPS

include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtDialect.td"
include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtInterface.td"

include "mlir/Interfaces/ControlFlowInterfaces.td"
include "mlir/Interfaces/DestinationStyleOpInterface.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"
include "mlir/Interfaces/TilingInterface.td"
include "mlir/Interfaces/ViewLikeInterface.td"

//===----------------------------------------------------------------------===//
// Base class.
//===----------------------------------------------------------------------===//
class NNCVLinalgExt_PureOp<string mnemonic, list<Trait> traits = []> :
    Op<NNCV_LinalgExt_Dialect, mnemonic, traits> {
}

class NNCVLinalgExt_Op<string mnemonic, list<Trait> traits = []> : NNCVLinalgExt_PureOp<mnemonic, !listconcat(traits, [
    AttrSizedOperandSegments,
    DeclareOpInterfaceMethods<MemoryEffectsOpInterface>,
    DestinationStyleOpInterface, LinalgExtInterface,
    SingleBlockImplicitTerminator<"::mlir::nncv::linalg_ext::YieldOp">
  ])> {
  let hasVerifier = 1;
  let hasCustomAssemblyFormat = 1;
  code extraLinalgExtOpClassDeclaration = "";
}

//===----------------------------------------------------------------------===//
// LinalgExt YieldOp.
//===----------------------------------------------------------------------===//
def NNCVLinalgExt_YieldOp : NNCVLinalgExt_PureOp<"yield", [Pure, ReturnLike, Terminator]> {
  let summary = "LinalgExt yield op";
  let description = [{
    `nncv_linalg_ext.yield` is a special terminator operation for blocks inside
    regions in `nncv_linalg_ext` ops.
  }];

  let arguments = (ins Variadic<AnyType>:$operands);

  let builders = [
    OpBuilder<(ins), [{ /* nothing to do */ }]>,
  ];

  let assemblyFormat = "attr-dict ($operands^ `:` type($operands))?";
}

//===----------------------------------------------------------------------===//
// Winograd Input and Output class.
//===----------------------------------------------------------------------===//
def NNCVLinalgExt_WinogradInputTransformOp : NNCVLinalgExt_Op<"winograd.input_transform",
    [DeclareOpInterfaceMethods<ReifyRankedShapedTypeOpInterface>,
     DeclareOpInterfaceMethods<TilingInterface,
      ["getIterationDomain",
       "getLoopIteratorTypes",
       "getResultTilePosition",
       "getTiledImplementation"]>]> {
  let summary = "Winograd Input Transform operator";
  let description = [{
    This operator is the first step in converting a convolution to
    its Winograd equivalent. Given a tile of an input image (I),
    this operator computes matmul(tranpose(B), matmul(I, B)).
    The input tile is assumed to be square with each side of size m + r - 1,
    where the convolutional kernel is m x m and the output tile size is r x r.
    B is a constant 2-d square matrix of the same shape as the input tile I.
    The input to the operator is an image of shape (N, H, W, C) or (N, C, H, W)
    and the output is an operator of shape (m + r - 1, m + r - 1, N, H', W', C)
    where H' = ceil((H - m + 1)/r) and W' = ceil((W - m + 1)/r). The result
    of this operator is first collapsed and then fed to a batch matmul op.
  }];

  let arguments = (ins Variadic<AnyShaped>:$inputs,
                       Variadic<AnyShaped>:$outputs,
                       I64Attr:$output_tile_size,
                       I64Attr:$kernel_size,
                       DenseI64ArrayAttr:$image_dimensions
  );

  let builders = [
    OpBuilder<(ins "ValueRange":$inputs, "ValueRange":$outputs,
      CArg<"int64_t", "8">:$output_tile_size, CArg<"int64_t", "3">:$kernel_size,
      CArg<"ArrayRef<int64_t>", "{1, 2}">:$image_dimensions)>
  ];

  let results = (outs Variadic<AnyRankedTensor>:$result);
  let hasFolder = 1;
  let assemblyFormat = [{
    attr-dict
    `output_tile_size` `(` $output_tile_size `)`
    `kernel_size` `(` $kernel_size `)`
    `image_dimensions` `(` $image_dimensions `)`
    `ins` `(` $inputs `:` type($inputs) `)`
    `outs` `(` $outputs `:` type($outputs) `)`
    (`->` type($result)^)?
  }];

  let extraClassDeclaration = extraLinalgExtOpClassDeclaration # [{
    Value input() {
      return getDpsInputOperand(0)->get();
    }
    Value output() {
      return getDpsInitOperand(0)->get();
    }
    ShapedType getInputOperandType() {
      return input().getType().cast<ShapedType>();
    }
    ShapedType getOutputOperandType() {
      return output().getType().cast<ShapedType>();
    }
    int64_t getInputOperandRank() {
      return getInputOperandType().getRank();
    }
    int64_t getOutputOperandRank() {
      return getOutputOperandType().getRank();
    }
    int64_t getInputTileSize() {
      return getOutputTileSize() + getKernelSize() - 1;
    }
    SmallVector<int64_t> imageDimensions() {
      return llvm::to_vector(getImageDimensions());
    }
    std::array<int64_t, 2> nhwcImageDimensions() {
      return {1, 2};
    }
    std::array<int64_t, 2> nchwImageDimensions() {
      return {2, 3};
    }
    bool isNhwc() {
      std::array<int64_t, 2> nhwcImageDims = nhwcImageDimensions();
      SmallVector<int64_t> imageDims = imageDimensions();
      return imageDims == ArrayRef<int64_t>(nhwcImageDims);
    }
    bool isNchw() {
      std::array<int64_t, 2> nchwImageDims = nchwImageDimensions();
      SmallVector<int64_t> imageDims = imageDimensions();
      return imageDims == ArrayRef<int64_t>(nchwImageDims);
    }
    int channelDim() {
      return isNhwc() ? 3 : 1;
    }
    int64_t getIterationDomainRank() {
      SmallVector<int64_t> imageDims = imageDimensions();
      return getInputOperandRank() - imageDims.size();
    }
    // Method to implement for specifying output range for
    // DestinationStyleOpInterface
    MutableOperandRange getDpsInitsMutable() {
      return getOutputsMutable();
    }
  }];
}

def NNCVLinalgExt_WinogradOutputTransformOp : NNCVLinalgExt_Op<"winograd.output_transform",
    [DeclareOpInterfaceMethods<ReifyRankedShapedTypeOpInterface>,
     DeclareOpInterfaceMethods<TilingInterface,
      ["getIterationDomain",
       "getLoopIteratorTypes",
       "getResultTilePosition",
       "getTiledImplementation"]>]> {
  let summary = "Winograd Output Transform operator";
  let description = [{
    This operator is the last transform in converting a convolution to
    its Winograd equivalent. After convolution in the Winograd domain
    (which turns into an elementwise product for a single channel and
    batch matrix multiplication for many channels), this operator converts
    the output back into the original domain. Given a tile of the
    output (O) in the Winograd domain, this operator computes
    matmul(transpose(A), matmul(O, A)). The output tile is square with
    each side of size m + r - 1, where the convolutional kernel is m x m
    and the output tile size is r x r. A is a constant 2-d matrix of
    shape (m + r - 1) x r. The input to the operator is a tensor of
    shape (m + r - 1, m + r - 1, N, H', W', C) and the output is a
    tensor of shape (N, H, W, C) or (N, C, H, W) where H = r H' and W = r W'.
    This operator is followed by a tensor.extract_slice which extracts
    only the non-padded part of the output.
  }];

  let arguments = (ins Variadic<AnyShaped>:$inputs,
                       Variadic<AnyShaped>:$outputs,
                       I64Attr:$output_tile_size,
                       I64Attr:$kernel_size,
                       DenseI64ArrayAttr:$image_dimensions
  );

  let builders = [
    OpBuilder<(ins "ValueRange":$inputs, "ValueRange":$outputs,
      CArg<"int64_t", "8">:$output_tile_size, CArg<"int64_t", "3">:$kernel_size,
      CArg<"ArrayRef<int64_t>", "{1, 2}">:$image_dimensions)>
  ];

  let results = (outs Variadic<AnyRankedTensor>:$result);
  let hasFolder = 1;
  let assemblyFormat = [{
    attr-dict
    `output_tile_size` `(` $output_tile_size `)`
    `kernel_size` `(` $kernel_size `)`
    `image_dimensions` `(` $image_dimensions `)`
    `ins` `(` $inputs `:` type($inputs) `)`
    `outs` `(` $outputs `:` type($outputs) `)`
    (`->` type($result)^)?
  }];

  let extraClassDeclaration = extraLinalgExtOpClassDeclaration # [{
    Value input() {
      return getDpsInputOperand(0)->get();
    }
    Value output() {
      return getDpsInitOperand(0)->get();
    }
    ShapedType getInputOperandType() {
      return input().getType().cast<ShapedType>();
    }
    ShapedType getOutputOperandType() {
      return output().getType().cast<ShapedType>();
    }
    SmallVector<int64_t> imageDimensions() {
      return llvm::to_vector(getImageDimensions());
    }
    std::array<int64_t, 2> nhwcImageDimensions() {
      return {1, 2};
    }
    std::array<int64_t, 2> nchwImageDimensions() {
      return {2, 3};
    }
    bool isNhwc() {
      std::array<int64_t, 2> nhwcImageDims = nhwcImageDimensions();
      SmallVector<int64_t> imageDims = imageDimensions();
      return imageDims == ArrayRef<int64_t>(nhwcImageDims);
    }
    bool isNchw() {
      std::array<int64_t, 2> nchwImageDims = nchwImageDimensions();
      SmallVector<int64_t> imageDims = imageDimensions();
      return imageDims == ArrayRef<int64_t>(nchwImageDims);
    }
    int channelDim() {
      return isNhwc() ? 3 : 1;
    }
    int64_t getInputOperandRank() {
      return getInputOperandType().getRank();
    }
    int64_t getOutputOperandRank() {
      return getOutputOperandType().getRank();
    }
    int64_t getIterationDomainRank() {
      SmallVector<int64_t> imageDims = imageDimensions();
      return getOutputOperandRank() - imageDims.size();
    }
    int64_t getInputTileSize() {
      return getOutputTileSize() + getKernelSize() - 1;
    }
    // Method to implement for specifying output range for
    // DestinationStyleOpInterface
    MutableOperandRange getDpsInitsMutable() {
      return getOutputsMutable();
    }
  }];
}

#endif //! NNCV_LINALGEXT_OPS