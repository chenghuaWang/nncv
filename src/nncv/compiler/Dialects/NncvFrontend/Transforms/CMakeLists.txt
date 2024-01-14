add_mlir_library(NncvFrontendPasses
# Source file.
    Passes.cpp
    MLProgramBufferize.cpp
    Conv2d1x1ToMatMul.cpp
    Conv2dToImgToCol.cpp
    PadLinalgOpsToIntMultiple.cpp
    InterchangeGenericOps.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SRC_DIR}/include/nncv/compiler/Dialects/NncvFrontend/Transforms

    DEPENDS
    NncvFrontendPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRIR
    MLIRTransforms
    MLIRMathTransforms
    MLIRLinalgTransforms
)
mlir_check_all_link_libraries(NncvFrontendPasses)