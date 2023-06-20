# set(DIALECTS_AUTOTEN_DIR_INCLUDE ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Dialects/AutoTen)
# set(DIALECTS_AUTOTEN_DIR_SRC ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Dialects/AutoTen)

set(LLVM_TARGET_DEFINITIONS AutoTen.td)
mlir_tablegen(AutoTen.h.inc -gen-op-decls)
mlir_tablegen(AutoTen.cpp.inc -gen-op-defs)
mlir_tablegen(Dialect.h.inc -gen-dialect-decls)
mlir_tablegen(Dialect.cpp.inc -gen-dialect-defs)
add_public_tablegen_target(Dialect_AutoTen_Target)