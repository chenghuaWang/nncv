include_directories(${PROJECT_SOURCE_DIR}/include/)
add_executable(alloc_test ./alloc/test.cpp)
if (nncv_enable_cuda)
    target_link_libraries(alloc_test libnncv-cuda)
else ()
    target_link_libraries(alloc_test libnncv-cpu)
endif()

enable_testing()
add_test(libnncv-test alloc_test)

# Other test unit
add_subdirectory(MemSolver)
add_subdirectory(Rt)