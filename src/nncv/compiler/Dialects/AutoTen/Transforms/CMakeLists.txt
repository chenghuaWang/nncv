add_mlir_library(AtenLangTransformsPasses
# Source file.
    Passes.cpp
    EliminateRetLoad.cpp
    EliminateRedundantStoreLoadForScf.cpp
    RaiseMemerefLSInAffineToAffineLS.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SRC_DIR}/include/nncv/compiler/Dialects/AutoTen/Transforms

    DEPENDS
    AtenLangTransformsPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRIR
    MLIRTransforms
    MLIRMathTransforms
    MLIRLinalgTransforms
)
mlir_check_all_link_libraries(AtenLangTransformsPasses)