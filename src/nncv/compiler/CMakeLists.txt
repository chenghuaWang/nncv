# CMake For MLIR Based Compiler.
set(CMAKE_CXX_STANDARD 17)

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

    DEPENDS
    Dialect_AutoTen_Target
)

target_link_libraries(nncv-c PRIVATE
    ${LLVM_LIBS}
    MLIRAnalysis
    MLIRIR
    MLIRParser
    MLIRPass
    MLIRSideEffectInterfaces
    MLIRTransforms
)
llvm_update_compile_flags(nncv-c)
