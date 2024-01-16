#ifndef NNCV_LINALGEXT_INTERFACES
#define NNCV_LINALGEXT_INTERFACES

include "nncv/compiler/Dialects/LinalgExt/IR/LinalgExtDialect.td"

def LinalgExtInterface : OpInterface<"LinalgExtOp"> {
  let methods = [];

  let extraClassDeclaration = [{
    LogicalResult reifyResultShapes(OpBuilder &b,
        mlir::ReifiedRankedShapedTypeDims &reifiedReturnShapes);

    void setNumInputs(unsigned num) { setOperandSegmentAt(0, num); }
    void setNumOutputBuffers(unsigned num) { setOperandSegmentAt(1, num); }

    private:
    void setOperandSegmentAt(unsigned idx, unsigned val) {
      auto attr = (*this)->getAttr("operand_segment_sizes")
        .cast<DenseIntElementsAttr>();
      unsigned i = 0;
      auto newAttr = attr.mapValues(IntegerType::get(getContext(), 32),
        [&](const APInt &v) { return (i++ == idx) ? APInt(32, val) : v; });
      getOperation()->setAttr("operand_segment_sizes", newAttr);
    }
  }];

  let verify = [{ return detail::verifyLinalgExtOpInterface($_op); }];
}

#endif  //! NNCV_LINALGEXT_INTERFACES