#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "suffix_array.hpp"

using namespace std;

TEST(SA, Naive) {
    SuffixArray sa("banana");
    vector<int> expect{5, 3, 1, 0, 4, 2};
    sa.BuildNaive();
    auto arr = sa.SA();
    for (size_t i = 0; i < 6; i++) {
        EXPECT_TRUE(arr[i] == expect[i]);
    } 
}

TEST(SA, NormalSort) {
    SuffixArray sa("banana");
    vector<int> expect{5, 3, 1, 0, 4, 2};
    // sa.BuildNormalSort();
    sa.BuildNormalSort();
    auto arr = sa.SA();
    for (size_t i = 0; i < 6; i++) {
        EXPECT_TRUE(arr[i] == expect[i]);
    } 
}

TEST(SA, RadixSort) {
    SuffixArray sa("banana");
    vector<int> expect{5, 3, 1, 0, 4, 2};
    // sa.BuildRadixSort();
    sa.BuildRadixSort();
    auto arr = sa.SA();
    for (size_t i = 0; i < 6; i++) {
        EXPECT_TRUE(arr[i] == expect[i]);
    } 

    EXPECT_TRUE(sa.LCP(0, 1) == 0);
    EXPECT_TRUE(sa.LCP(1, 3) == 3);
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
