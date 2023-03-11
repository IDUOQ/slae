cmake_minimum_required(VERSION 3.22)
project(slae_1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

OPTION(TESTS "Enable testing of the project" ON)
if (TESTS)
    add_compile_definitions(COMPILE_WITH_TESTS)
    add_subdirectory(tests)
    message("TESTING ENABLED")
else()
    message("TESTING DISABLED")
endif()
