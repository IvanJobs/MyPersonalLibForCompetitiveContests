#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "binary_index_tree.hpp"

using namespace std;

TEST(FenwickBasic, RangeSum) {
    FenwickTree fw(4);
    vector<int> a {1, 3, 2, 4};
    for (auto i = 0; i < 4; i++) {
        fw.Update(i + 1, a[i]);
    }

    EXPECT_TRUE(fw.RangeSum(1, 1) == 1);
    EXPECT_TRUE(fw.RangeSum(1, 2) == 4);
    EXPECT_TRUE(fw.RangeSum(1, 3) == 6);
    
    fw.Update(3, 2);
    EXPECT_TRUE(fw.RangeSum(3, 3) == 4);
    EXPECT_TRUE(fw.RangeSum(1, 2) == 4);
    EXPECT_TRUE(fw.RangeSum(2, 4) == 11);
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
