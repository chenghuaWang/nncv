project(nncv_interface LANGUAGES CXX)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

python_add_library(_C MODULE src/pynncv.cpp WITH_SOABI)
target_link_libraries(_C PRIVATE pybind11::headers)

install(TARGETS _C DESTINATION python)
