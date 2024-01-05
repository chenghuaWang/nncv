add_mlir_library(
    NncvRunner
    MLProgramBufferize.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SRC_DIR}/include/nncv

    DEPENDS
    NncvRunnerPassIncGen

    LINK_COMPONENTS
    Core

    LINK_LIBS PUBLIC
    MLIRIR
    MLIRTransforms
    MLIRMathTransforms
    MLIRLinalgTransforms
)
mlir_check_all_link_libraries(NncvRunner)