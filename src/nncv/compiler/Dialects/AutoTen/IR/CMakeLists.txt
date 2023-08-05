add_mlir_dialect_library(MLIRAtenLang

    AtenDialect.cpp
    AtenAttrs.cpp
    AtenTypes.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/include/nncv

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