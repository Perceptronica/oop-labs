
/*
#include "../lib/vector.h"
#include <gtest/gtest.h>
#include <map>
#include <vector>

TEST(test_01, allocator_checker) {
    std::vector<int> std_vector;
    lab5::vector<int> my_vector;
    const int SIZE = 100;
    for (size_t i {0}; i < SIZE; ++i) {
        std_vector.push_back(i);
        my_vector.push_back(i);
    }

    for (size_t i {0}; i < SIZE; ++i) {
        EXPECT_EQ(std_vector[i], my_vector[i]);
    }
}


TEST(test_02, allocator_memory_left) {
    using alloc = lab5::allocator<int>;
    alloc allocator;
    EXPECT_THROW(std::allocator_traits<alloc>::allocate(allocator, 10000), std::logic_error);
}
*/