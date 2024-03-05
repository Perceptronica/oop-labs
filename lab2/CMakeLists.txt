cmake_minimum_required(VERSION 3.20)

project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2 src/Thirteen.cpp src/main.cpp lib/Thirteen.h)
add_executable(tests2 tests/tests.cpp)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(tests2 PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(NAME LAB2 COMMAND tests2)