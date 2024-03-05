cmake_minimum_required(VERSION 3.20)

project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMPILE_FILES
    lib/Figure.h
    lib/Point.h
    lib/Rectangle.h
    lib/Segment.h
    lib/Validators.h
    lib/Square.h
    lib/Trapezoid.h
)

add_executable(lab3 src/main.cpp ${COMPILE_FILES})
add_executable(tests3 tests/tests.cpp)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(tests3 PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(NAME LAB3 COMMAND tests3)