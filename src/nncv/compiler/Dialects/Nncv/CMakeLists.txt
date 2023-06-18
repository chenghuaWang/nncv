set(DIALECTS_NNCVIR_DIR_INCLUDE ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Dialects/Nncv)
set(DIALECTS_NNCVIR_DIR_SRC ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Dialects/Nncv)

set(LLVM_TARGET_DEFINITIONS Nncv.td)
mlir_tablegen(Nncv.h.inc -gen-op-decls)
mlir_tablegen(Nncv.cpp.inc -gen-op-defs)
mlir_tablegen(NncvDialect.h.inc -gen-dialect-decls)
mlir_tablegen(NncvDialect.cpp.inc -gen-dialect-defs)
add_public_tablegen_target(Dialect_NNCVIR_Target)