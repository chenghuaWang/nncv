set(CMAKE_CXX_STANDARD 17)

add_library(nncv_rt
SHARED
    ${PROJECT_SOURCE_DIR}/src/libnncv/DataType.cpp
    ${PROJECT_SOURCE_DIR}/src/libnncv/SystemIo.cpp
    ${PROJECT_SOURCE_DIR}/include/libnncv/DataType.hpp
    ${PROJECT_SOURCE_DIR}/include/libnncv/SystemIo.hpp
)