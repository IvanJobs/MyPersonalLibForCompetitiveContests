#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include "radix_sort.hpp"

using namespace std;

TEST(RadixSort, Pre) {
    EXPECT_TRUE(RadixSort::IntWidth(0) == 1);
    EXPECT_TRUE(RadixSort::IntWidth(12) == 2);
    EXPECT_TRUE(RadixSort::IntWidth(123) == 3);
    EXPECT_TRUE(RadixSort::IntWidth(1234) == 4);
    EXPECT_TRUE(RadixSort::IntWidth(12345) == 5);
    EXPECT_TRUE(RadixSort::IntWidth(123456) == 6);

    EXPECT_TRUE(RadixSort::GetShiftValue(123, 1) == 3);
    EXPECT_TRUE(RadixSort::GetShiftValue(123, 2) == 2);
    EXPECT_TRUE(RadixSort::GetShiftValue(123, 3) == 1);
    EXPECT_TRUE(RadixSort::GetShiftValue(123, 4) == 0);
    EXPECT_TRUE(RadixSort::GetShiftValue(123, 5) == 0);
    EXPECT_TRUE(RadixSort::GetShiftValue(123, 6) == 0);
}

TEST(RadixSort, RadixSort) {
    vector<int> v {11, 22, 34, 9, 21, 18, 1000, 550};
    vector<int> r {9, 11, 18, 21, 22, 34, 550, 1000};
    RadixSort::Sort(v);
    for (size_t i = 0; i < v.size(); i++) {
        EXPECT_TRUE(v[i] == r[i]);
    }
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
