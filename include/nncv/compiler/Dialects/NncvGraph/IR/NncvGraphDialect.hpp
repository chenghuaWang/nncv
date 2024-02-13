#ifndef NNCV_C_NNCV_GRAPH_DIALECT_HPP_
#define NNCV_C_NNCV_GRAPH_DIALECT_HPP_

#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/SymbolTable.h"

namespace mlir {
namespace nncv {
namespace graph {

class NncvGraphDialect : public Dialect {
 public:
  explicit NncvGraphDialect(MLIRContext* context);
  static StringRef getDialectNamespace() { return "NncvGraphDialect"; }

  Operation* materializeConstant(OpBuilder& builder, Attribute value, Type type,
                                 Location loc) override;

  Attribute parseAttribute(DialectAsmParser& parser, Type type) const override;
  void printAttribute(Attribute attr, DialectAsmPrinter& p) const override;

  Type parseType(DialectAsmParser& parser) const override;
  void printType(Type type, DialectAsmPrinter& p) const override;

  static bool isDialectOp(Operation* op) {
    return op && op->getDialect() && op->getDialect()->getNamespace() == getDialectNamespace();
  }

 private:
  void registerAttributes();
  void registerTypes();
};

}  // namespace graph
}  // namespace nncv
}  // namespace mlir

#endif  //! NNCV_C_NNCV_GRAPH_DIALECT_HPP_