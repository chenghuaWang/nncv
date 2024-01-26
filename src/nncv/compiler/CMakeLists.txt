# CMake For MLIR Based Compiler.
set(CMAKE_CXX_STANDARD 17)

option(nncv_compiler_use_antlr "Enable antlr for frontend" ON)


if (nncv_compiler_use_antlr)

if (MSVC)
    set(ANTLR4_WITH_STATIC_CRT OFF)
endif()

add_definitions(-DNNCV_ENABLE_ANTLR=1)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/antlr)
add_definitions(-DANTLR4CPP_STATIC)
set(ANTLR_EXECUTABLE ${PROJECT_SOURCE_DIR}/third_party/antlr/antlr-4.13.0-complete.jar)
set(ANTLR4_ZIP_REPOSITORY ${PROJECT_SOURCE_DIR}/third_party/antlr/antlr4-4.13.0.zip)
include(ExternalAntlr4Cpp)

include_directories(${ANTLR4_INCLUDE_DIRS})
link_directories(${ANTLR4CPP_LIBS})

include_directories(${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/)

message( STATUS "Antlr is set to ${ANTLR4_INCLUDE_DIRS}")
find_package(ANTLR REQUIRED)

endif (nncv_compiler_use_antlr)

find_package(Protobuf CONFIG REQUIRED)
if(${Protobuf_FOUND})
    # TODO add some args and include libs, etc.
    message( STATUS "Found Protobuf at ${Protobuf_INCLUDE_DIRS}")
    include_directories(Protobuf_INCLUDE_DIRS)
else()
    message( FATAL_ERROR "Protobuf not found")
endif()

find_package(fmt CONFIG REQUIRED)

# Add Dialets into this project
add_subdirectory(Dialects)
# Add Convertion into this project
add_subdirectory(Conversion)
# Add all include to this project

get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
get_property(extension_libs GLOBAL PROPERTY MLIR_EXTENSION_LIBS)

# The compiler target
add_llvm_executable(nncv-c
    # Cli Driver files
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/main.cpp

    # Parser, Lexer and AST
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/TenLangLexer.cpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/TenLangParser.cpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/TenLangPreprocess.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/TenLangLexer.hpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/TenLangParser.hpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/TenLangPreprocess.hpp

    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/AntlrBackend/AutoTenV1Lexer.cpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/AntlrBackend/AutoTenV1Parser.cpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserBaseListener.cpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserBaseVisitor.cpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserListener.cpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserVisitor.cpp

    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/BuiltinMethodHandler.hpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1Lexer.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1Parser.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserBaseListener.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserBaseVisitor.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserListener.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserVisitor.h

    # Pipeline
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Pipeline/Frontend.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Pipeline/Frontend.hpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Pipeline/LinalgTensorLowering.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Pipeline/LinalgTensorLowering.hpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Pipeline/DnnModelLowering.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Pipeline/DnnModelLowering.hpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Pipeline/AtenBackendLowering.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Pipeline/AtenBackendLowering.hpp

    # CodeGen
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/CodeGenCtx.hpp

    # Optimizer
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Optimizer/MemSolver.hpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Optimizer/MemSolver.cpp

    # Utils
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Utils/CliFormatOutput.hpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Utils/STrap.hpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Utils/SymbolRef.hpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Utils/SymbolRef.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Utils/PlatformCtx.hpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Utils/MlirIo.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Utils/MlirIo.hpp

    # Runner
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Runner/InitJit.hpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Runner/InitAllPass.hpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Runner/RunnerCtx.hpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Runner/InitJit.cpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Runner/InitAllPass.cpp
)

set(LinkedLibs

    # common libs
    MLIRObservers
    MLIRSupport
    MLIRAnalysis
    MLIRBuiltinToLLVMIRTranslation
    MLIRCallInterfaces
    MLIRCastInterfaces
    MLIRExecutionEngine
    MLIRFunctionInterfaces
    MLIRIR
    MLIRLLVMCommonConversion
    MLIRLLVMToLLVMIRTranslation
    MLIRMemRefDialect
    MLIRParser
    MLIRPass
    MLIRSideEffectInterfaces
    MLIRTargetLLVMIRExport
    MLIRTransforms
    MLIRLinalgDialect
    MLIRLinalgTransforms
    MLIRLinalgUtils
    MLIRMathDialect
    MLIRMemRefTransforms
    MLIRPDLDialect
    MLIRPDLInterpDialect
    MLIRControlFlowDialect
    MLIRPluginsLib
    MLIRBufferizationDialect
    MLIRBufferizationPipelines
    MLIRBufferizationToMemRef
    MLIRBufferizationTransformOps
    MLIRBufferizationTransforms
    MLIRIRDL
    MLIRMemRefTransforms
    MLIRMemRefUtils

    # NNCV Libs
    # dialect itself
    MLIRAtenLang
    NNCVLinalgExtDialect
    # Pass
    NncvFrontendPasses
    AtenLangTransformsPasses
    NNCVLinalgExtPasses
    # convert pass
    ConvOptimizeConversion
    AtenToArithConversion
)

if (nncv_compiler_use_antlr)
    target_link_libraries(nncv-c PRIVATE
        ${LLVM_LIBS}
        ${dialect_libs}
        ${conversion_libs}
        ${extension_libs}

        ${LinkedLibs}

        # Third-party
        fmt::fmt-header-only

        # antlr4
        antlr4_static

        # cpu info
        cpuinfo
    )
else()
    target_link_libraries(nncv-c PRIVATE
        ${LLVM_LIBS}
        ${dialect_libs}
        ${conversion_libs}
        ${extension_libs}

        ${LinkedLibs}

        # Third-party
        fmt::fmt-header-only

        # Cpu info
        cpuinfo
    )
endif()

if (nncv_enable_cuda)
    target_link_libraries(nncv-c PRIVATE
        CUDA::cudart
    )
endif (nncv_enable_cuda)
mlir_check_all_link_libraries(nncv-c)
llvm_update_compile_flags(nncv-c)
