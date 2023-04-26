cmake_minimum_required(VERSION 3.18)
project(
    nncv
    LANGUAGES CXX CUDA
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
    message(STATUS "cuda version: " ${CUDA_VERSION_STRING})
    include_directories(${CUDA_INCLUDE_DIRS})
    add_definitions(-DNNCV_ENABLE_CUDA=1)
endif(nncv_enable_cuda)

include(cmake/check_simd.cmake)
CHECK_SIMD()

set(nncv_include_lists)
set(nncv_link_lib_lists)

if(nncv_enable_opencv)
    message(WARNING "As a light-weighted framework, OpenCV is too heavy, I not recommend you to use it.")
    message(STATUS "Using image io backend [opencv]")
    find_package(opencv REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    list(APPEND nncv_link_lib_lists ${OpenCV_LIBS})
endif(nncv_enable_opencv)

if(nncv_enable_stb_image)
    message(STATUS "Using image io backend [stb]")
# TODO
endif(nncv_enable_stb_image)

if(nncv_build_dynamic_lib)
    file(GLOB_RECURSE nncv_srcs_cpp ${PROJECT_SOURCE_DIR}/src/nncv/*.cpp)
    file(GLOB_RECURSE nncv_srcs_hpp ${PROJECT_SOURCE_DIR}/include/nncv/*.hpp)
if(nncv_enable_cuda)
    message(STATUS "Building NNCV Dynamic lib for CUDA Device")
    file(GLOB_RECURSE nncv_srcs_cu ${PROJECT_SOURCE_DIR}/src/nncv/*.cu)
    file(GLOB_RECURSE nncv_srcs_cuh ${PROJECT_SOURCE_DIR}/include/nncv/*.cuh)
    add_library(libnncv-cuda SHARED
        ${nncv_srcs_cpp}
        ${nncv_srcs_hpp}
        ${nncv_srcs_cu}
        ${nncv_srcs_cuh}
        ${nncv_include_lists}
    )
    add_compile_options(--cuda-gpu-arch=sm_20) # TODO change it.
    target_link_libraries(libnncv-cuda ${CUDA_LIBRARIES} ${nncv_link_lib_lists})
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
    # TODO
endif()
