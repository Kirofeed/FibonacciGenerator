cmake_minimum_required(VERSION 3.5)
project(IndustrialFibonacci)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

option(BUILD_TESTS "Build unit tests" ON)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(main src/main.cpp src/FibonacciGenerator.cpp)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(runTests test/test_FibonacciGenerator.cpp src/FibonacciGenerator.cpp)
    target_compile_definitions(runTests PRIVATE UNIT_TEST)
    target_link_libraries(runTests ${GTEST_LIBRARIES} gtest_main pthread)
    add_test(NAME runTests COMMAND runTests)
endif()

