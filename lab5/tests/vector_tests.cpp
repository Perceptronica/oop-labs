/*
#include "../lib/vector.h"
#include <gtest/gtest.h>

TEST(test_01, vector_push) {
    lab5::vector<int> v;
    v.push_back(10);
    EXPECT_EQ(v[0], 10);
}


TEST(test_02, vector_back) {
    lab5::vector<int> v;
    v.push_back(10);
    const int res = v.back();
    EXPECT_EQ(res, 10);
}


TEST(test_03, vector_index) {
    lab5::vector<int> v(10);
    v[5] = 10;
    EXPECT_EQ(*(&v[0] + 5), 10);
}


TEST(test_04, vector_at_success) {
    lab5::vector<int> v(10);
    int res = v.at(5);
    EXPECT_EQ(res, 0);
}


TEST(test_05, vector_index_out_of_range) {
    lab5::vector<int> v(10);
    EXPECT_THROW(v.at(11), std::out_of_range);
}


TEST(test_06, vector_empty) {
    lab5::vector<int> v;
    EXPECT_EQ(v.empty(), true);
}


TEST(test_07, vector_empty) {
    lab5::vector<int> v(2, 2);
    EXPECT_EQ(v.empty(), false);
}
*/