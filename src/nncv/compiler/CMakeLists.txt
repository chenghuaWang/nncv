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

unset(LLVM_DIR CACHE)
if (NOT DEFINED MLIR_DIR)
  message(FATAL_ERROR "MLIR_DIR is not configured but it is required. "
    "Set the cmake option MLIR_DIR, e.g.,\n"
    "    cmake -DMLIR_DIR=/path/to/llvm-project/build/lib/cmake/mlir ..\n"
    )
endif()
find_package(MLIR 
    REQUIRED 
    CONFIG
)

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)
set(MLIR_BINARY_DIR ${CMAKE_BINARY_DIR})

message(STATUS "LLVM_RUNTIME_OUTPUT_INTDIR: ${LLVM_RUNTIME_OUTPUT_INTDIR}")
message(STATUS "LLVM_LIBRARY_OUTPUT_INTDIR: ${LLVM_LIBRARY_OUTPUT_INTDIR}")

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

include(TableGen)
include(AddLLVM)
include(AddMLIR)
# include(HandleLLVMOptions)

set(BUILD_SHARED_LIBS ${LLVM_ENABLE_SHARED_LIBS} CACHE BOOL "" FORCE)
message(STATUS "BUILD_SHARED_LIBS        : " ${BUILD_SHARED_LIBS})

# nncv uses exceptions, so we need to make sure that LLVM_REQUIRES_EH is set to ON, so that
# the functions from HandleLLVMOptions and AddLLVM don't disable exceptions.
set(LLVM_REQUIRES_EH ON)
set(LLVM_ENABLE_RTTI ON)
message(STATUS "LLVM_REQUIRES_EH         : " ${LLVM_REQUIRES_EH})
message(STATUS "LLVM_ENABLE_RTTI         : " ${LLVM_ENABLE_RTTI})

message(STATUS "LLVM_INCLUDE_DIRS        : " ${LLVM_INCLUDE_DIRS})
message(STATUS "MLIR_INCLUDE_DIRS        : " ${MLIR_INCLUDE_DIRS})
message(STATUS "LLVM_BUILD_LIBRARY_DIR   : " ${LLVM_BUILD_LIBRARY_DIR})
message(STATUS "LLVM_DEFINITIONS         : " ${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(LLVM_LIBS support core irreader)
message(STATUS "LLVM_LIBS                : " ${LLVM_LIBS})

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
link_directories(D:/commonlib/llvm-project/build/Debug/lib)
add_definitions(${LLVM_DEFINITIONS})


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

    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1Lexer.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1Parser.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserBaseListener.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserBaseVisitor.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserListener.h
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Frontend/AntlrBackend/AutoTenV1ParserVisitor.h

    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Pipeline/Frontend.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Pipeline/Frontend.hpp

    # Utils
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Utils/CliFormatOutput.hpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Utils/STrap.hpp

    DEPENDS
    Dialect_AutoTen_Target
)

if (nncv_compiler_use_antlr)
    target_link_libraries(nncv-c PRIVATE
    ${LLVM_LIBS}
    MLIRAnalysis
    MLIRIR
    MLIRParser
    MLIRPass
    MLIRSideEffectInterfaces
    MLIRTransforms

    # Third-party
    fmt::fmt-header-only

    # antlr4
    antlr4_static
    )
else()
    target_link_libraries(nncv-c PRIVATE
        ${LLVM_LIBS}
        MLIRAnalysis
        MLIRIR
        MLIRParser
        MLIRPass
        MLIRSideEffectInterfaces
        MLIRTransforms

        # Third-party
        fmt::fmt-header-only
    )
endif()

llvm_update_compile_flags(nncv-c)
