add_mlir_dialect_library(MLIRNncvGraphDialect
    NncvGraphInterfaces.cpp
    NncvGraphOps.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/nncv/Dialects/NncvGraph/IR

    DEPENDS
    MLIRAutoTenOpsIncGen
    MLIRAutoTenEnumsGen

    LINK_LIBS PUBLIC
    MLIRIR
    MLIRSupport
    MLIRSideEffectInterfaces

    MLIRCallInterfaces
    MLIRCastInterfaces
    MLIRControlFlowInterfaces
    MLIRDataLayoutInterfaces
    MLIRInferTypeOpInterface
)