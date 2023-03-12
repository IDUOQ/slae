add_subdirectory(googletest)

include_directories(googletest/googletest/src
        ../src/tridiag_solver ../src/dense_matrix
        ../src/tridiag_matrix ../src/gauss_seidel_method
        ../src/csr_matrix ../src/jacobi_method
        ../src/simple_iteration_method)

add_executable(run_tests tests.cpp)

target_link_libraries(run_tests gtest gtest_main SLAE_methods)

file(GLOB_RECURSE matrixes_for_tests "matrixes/*.txt")

file(COPY ${matrixes_for_tests}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


