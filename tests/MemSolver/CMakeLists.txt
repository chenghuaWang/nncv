add_executable(memsolver_test
    test.cpp
    ${PROJECT_SOURCE_DIR}/include/nncv/compiler/Optimizer/MemSolver.hpp
    ${PROJECT_SOURCE_DIR}/src/nncv/compiler/Optimizer/MemSolver.cpp
)
add_test(memsolver-test memsolver_test)