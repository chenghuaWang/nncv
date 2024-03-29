cmake_minimum_required(VERSION 3.20)

# for Windows' users.
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/vcpkg/scripts/buildsystems/vcpkg.cmake)
message( STATUS "CMAKE_TOOLCHAIN_FILE is setting to ${CMAKE_TOOLCHAIN_FILE}")

project(
    nncv
    LANGUAGES C CXX
    VERSION 0.0.1
)

set(CMAKE_INSTALL_MESSAGE LAZY CACHE STRING "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

option(nncv_enable_cuda "Enable CUDA Device will involve cuh file to op" ON)
option(nncv_enable_opencv "Eanbel opencv for image preprocessing" OFF)
option(nncv_enable_stb_image "Enable std image for read/write image, preprocessing is limited" ON)
option(nncv_build_dynamic_lib "Build the dynamic lib of nncv" ON)
option(nncv_build_examples "Build Examples" OFF)
option(nncv_build_test "Build Test module" ON)
option(nncv_build_python_toolset "Build Python toolset for quickly test" OFF)
option(nncv_build_model_compiler "Build model compiler for optimize kernel" ON)
option(nncv_build_vm "Build Virtual machine for execute networks" ON)
option(nncv_build_visual_profiler "Build nncv visual profiler" ON)
# Reference:
# https://medium.com/@alasher/colored-c-compiler-output-with-ninja-clang-gcc-10bfe7f2b949
option(nccv_force_colored_diagnostics "Always produce ANSI-colored diagnostics (GNU/Clang only)." ON)

if(nccv_force_colored_diagnostics)
  add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:GNU>:-fdiagnostics-color=always>>
    $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:Clang>:-fcolor-diagnostics>>
    $<$<COMPILE_LANGUAGE:CUDA>:$<$<CUDA_COMPILER_ID:Clang>:-fcolor-diagnostics>>)
endif(nccv_force_colored_diagnostics)

if(APPLE)
if(nncv_enable_cuda)
    message(FATAL_ERROR "APPLE Device do not support CUDA Device anymore !!!")
    EXIT()
endif(nncv_enable_cuda)
endif(APPLE)

if(nncv_enable_cuda)
    enable_language(CUDA)
    find_package(CUDAToolkit)
    message ( STATUS  "CUDAToolkit_FOUND=${CUDAToolkit_FOUND}" )
    message ( STATUS  "CUDAToolkit_VERSION=${CUDAToolkit_VERSION}" )
    message ( STATUS  "CUDAToolkit_VERSION_MAJOR=${CUDAToolkit_VERSION_MAJOR}" )
    message ( STATUS  "CUDAToolkit_VERSION_MINOR=${CUDAToolkit_VERSION_MINOR}" )
    message ( STATUS  "CUDAToolkit_VERSION_PATCH=${CUDAToolkit_VERSION_PATCH}" )
    message ( STATUS  "CUDAToolkit_BIN_DIR=${CUDAToolkit_BIN_DIR}" )
    message ( STATUS  "CUDAToolkit_INCLUDE_DIRS=${CUDAToolkit_INCLUDE_DIRS}" )
    message ( STATUS  "CUDAToolkit_LIBRARY_DIR=${CUDAToolkit_LIBRARY_DIR}" )
    message ( STATUS  "CUDAToolkit_LIBRARY_ROOT=${CUDAToolkit_LIBRARY_ROOT}" )
    message ( STATUS  "CUDAToolkit_TARGET_DIR=${CUDAToolkit_TARGET_DIR}" )
    message ( STATUS  "CUDAToolkit_NVCC_EXECUTABLE=${CUDAToolkit_NVCC_EXECUTABLE}" )
    include_directories(${CUDAToolkit_INCLUDE_DIRS})
    add_definitions(-DNNCV_ENABLE_CUDA=1)
endif(nncv_enable_cuda)

include(cmake/check_simd.cmake)
include(cmake/check_statement_expr.cmake)
CHECK_SIMD()
# CHECK_STATEMENT_EXPR()

set(nncv_include_lists)
set(nncv_link_lib_lists)
set(nncv_3rd_src_list)
set(nncv_3rd_include_list)

add_subdirectory(third_party/cpuinfo EXCLUDE_FROM_ALL)

if(nncv_enable_opencv)
    message(WARNING "As a light-weighted framework, OpenCV is too heavy, I not recommend you to use it.")
    message(STATUS "Using image io backend [opencv]")
    find_package(opencv REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    list(APPEND nncv_link_lib_lists ${OpenCV_LIBS})
    add_definitions(-DNNCV_ENABLE_OPENCV=1)
else()
    add_definitions(-DNNCV_ENABLE_OPENCV=0)
endif(nncv_enable_opencv)

if(nncv_enable_stb_image)
    message(STATUS "Using image io backend [stb]")
    add_definitions(-DNNCV_ENABLE_STB_IMAGE=1)
    list(APPEND nncv_include_lists ${PROJECT_SOURCE_DIR}/third_party/stb_image/stb_image.h)
    # list(APPEND nncv_3rd_include_list ${PROJECT_SOURCE_DIR}/third_party/stb_image/stb_image.h)
    # list(APPEND nncv_3rd_src_list ${PROJECT_SOURCE_DIR}/third_party/stb_image/stb_image.cpp)
    include_directories(${PROJECT_SOURCE_DIR}/third_party/)
else()
    add_definitions(-DNNCV_ENABLE_STB_IMAGE=0)
endif(nncv_enable_stb_image)

if(nncv_build_dynamic_lib)
    file(GLOB_RECURSE nncv_srcs_cpp ${PROJECT_SOURCE_DIR}/src/nncv/core/*.cpp)
    file(GLOB_RECURSE nncv_srcs_hpp ${PROJECT_SOURCE_DIR}/include/nncv/core/*.hpp)
if(nncv_enable_cuda)
    message(STATUS "Building NNCV Dynamic lib for CUDA Device")
    file(GLOB_RECURSE nncv_srcs_cu ${PROJECT_SOURCE_DIR}/src/nncv/core/*.cu)
    file(GLOB_RECURSE nncv_srcs_cuh ${PROJECT_SOURCE_DIR}/include/nncv/core/*.cuh)
    add_library(libnncv-cuda SHARED
        ${nncv_srcs_cpp}
        ${nncv_srcs_hpp}
        ${nncv_srcs_cu}
        ${nncv_srcs_cuh}
        ${nncv_include_lists}
    )
    target_link_libraries(libnncv-cuda ${nncv_link_lib_lists})
    include_directories(libnncv-cuda ${PROJECT_SOURCE_DIR}/include/)
else()
    message(STATUS "Building NNCV Dynamic lib for CPU on X86")
    add_library(libnncv-cpu SHARED
        ${nncv_srcs_cpp}
        ${nncv_srcs_hpp}
        ${nncv_include_lists}
    )
    target_link_libraries(libnncv-cpu ${nncv_link_lib_lists})
    include_directories(libnncv-cpu ${PROJECT_SOURCE_DIR}/include/)
endif(nncv_enable_cuda)
endif(nncv_build_dynamic_lib)

if(nncv_build_examples)
    message(STATUS "Building NNCV Examples")
    add_subdirectory(${PROJECT_SOURCE_DIR}/examples)
endif(nncv_build_examples)

if(nncv_build_test)
    message(STATUS "Building NNCV Tests Module")
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif(nncv_build_test)

if(nncv_build_python_toolset)
    message(STATUS "Building NNCV Python Toolset")
    add_subdirectory(${PROJECT_SOURCE_DIR}/python)
endif(nncv_build_python_toolset)

if(nncv_build_visual_profiler)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/nncv/VisualProfiler)
endif()

if(nncv_build_vm)
    message(STATUS "Building NNCV Virtual Machine")
    file(GLOB_RECURSE nncv_vm_srcs_cpp ${PROJECT_SOURCE_DIR}/src/nncv/vm/*.cpp)
    file(GLOB_RECURSE nncv_vm_srcs_hpp ${PROJECT_SOURCE_DIR}/include/nncv/vm/*.hpp)
if(nncv_enable_cuda)
    file(GLOB_RECURSE nncv_vm_srcs_cu ${PROJECT_SOURCE_DIR}/src/nncv/vm/*.cu)
    file(GLOB_RECURSE nncv_vm_srcs_cuh ${PROJECT_SOURCE_DIR}/include/nncv/vm/*.cuh)
    add_executable(nncv-vm-cuda
        ${nncv_vm_srcs_cpp}
        ${nncv_vm_srcs_hpp}
        ${nncv_vm_srcs_cu}
        ${nncv_vm_srcs_cuh}
        ${nncv_3rd_include_list}
        ${nncv_3rd_src_list}
    )
    target_link_libraries(nncv-vm-cuda libnncv-cuda)
else()
    add_executable(nncv-vm-cpu
        ${nncv_vm_srcs_cpp}
        ${nncv_vm_srcs_hpp}
        ${nncv_3rd_include_list}
        ${nncv_3rd_src_list}
    )
    target_link_libraries(nncv-vm-cpu libnncv-cpu)
endif(nncv_enable_cuda)
endif(nncv_build_vm)

if(nncv_build_model_compiler)
    add_subdirectory(${PROJECT_SOURCE_DIR}/src/libnncv)

    message(STATUS "Building NNCV Modle Compiler")


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
    include(HandleLLVMOptions)

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
    add_definitions(${LLVM_DEFINITIONS})

    include_directories(${CMAKE_CURRENT_BINARY_DIR}/include/nncv/compiler/Dialects/)
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/include/nncv/compiler/Pipeline/)
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/include/nncv/compiler/)

    add_subdirectory(${PROJECT_SOURCE_DIR}/src/nncv/compiler)
    add_subdirectory(${PROJECT_SOURCE_DIR}/include/nncv/compiler)
endif(nncv_build_model_compiler)