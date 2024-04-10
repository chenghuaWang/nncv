set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 CONFIG REQUIRED)

add_library(nncv_rt
SHARED
    ${PROJECT_SOURCE_DIR}/src/libnncv/DataType.cpp
    ${PROJECT_SOURCE_DIR}/src/libnncv/SystemIo.cpp
    ${PROJECT_SOURCE_DIR}/include/libnncv/DataType.hpp
    ${PROJECT_SOURCE_DIR}/include/libnncv/SystemIo.hpp
    ${PROJECT_SOURCE_DIR}/src/libnncv/kernel/avx2/matmul.cpp
    ${PROJECT_SOURCE_DIR}/src/libnncv/kernel/avx2/conv2d.cpp
    ${PROJECT_SOURCE_DIR}/src/libnncv/kernel/avx2/utils.cpp
    ${PROJECT_SOURCE_DIR}/include/libnncv/kernel/avx2/matmul.hpp
    ${PROJECT_SOURCE_DIR}/include/libnncv/kernel/avx2/conv2d.hpp
    ${PROJECT_SOURCE_DIR}/include/libnncv/kernel/avx2/utils.hpp
)

include_directories(${EIGEN3_INCLUDE_DIR})
message(${EIGEN3_INCLUDE_DIR})
target_link_libraries(nncv_rt PRIVATE Eigen3::Eigen)