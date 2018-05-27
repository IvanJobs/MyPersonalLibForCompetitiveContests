#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include "radix_sort.hpp"

using namespace std;

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