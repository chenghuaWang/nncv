# set(DIALECTS_AUTOTEN_DIR_INCLUDE ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Dialects/AutoTen)
# set(DIALECTS_AUTOTEN_DIR_SRC ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Dialects/AutoTen)

set(LLVM_TARGET_DEFINITIONS AutoTen.td)
mlir_tablegen(AutoTen.h.inc -gen-op-decls)
mlir_tablegen(AutoTen.cpp.inc -gen-op-defs)

mlir_tablegen(Dialect.h.inc -gen-dialect-decls)
mlir_tablegen(Dialect.cpp.inc -gen-dialect-defs)

mlir_tablegen(AutoTenOpsEnums.h.inc -gen-enum-decls)
mlir_tablegen(AutoTenOpsEnums.cpp.inc -gen-enum-defs)

mlir_tablegen(AutoTenOpsAttributes.h.inc -gen-attrdef-decls -attrdefs-dialect=aten)
mlir_tablegen(AutoTenOpsAttributes.cpp.inc -gen-attrdef-defs -attrdefs-dialect=aten)

mlir_tablegen(AutoTenTypes.h.inc -gen-typedef-decls)
mlir_tablegen(AutoTenTypes.cpp.inc -gen-typedef-defs)

add_public_tablegen_target(Dialect_AutoTen_Target)