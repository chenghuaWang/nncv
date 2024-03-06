add_executable(nncv_rt_test
    test.cpp
)
target_link_libraries(nncv_rt_test nncv_rt)
add_test(nncv_rt-test nncv_rt_test)