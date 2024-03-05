cmake_minimum_required(VERSION 3.20)

project(lab5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab5 src/main.cpp)
add_executable(tests5 tests/allocator_tests.cpp tests/vector_tests.cpp)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(tests5 PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(NAME LAB5 COMMAND tests5)