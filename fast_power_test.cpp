#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "fast_power.hpp"

using namespace std;

TEST(FastPow, FastPow) {
    EXPECT_TRUE(FastPow(5, 0) == 1);
    EXPECT_TRUE(FastPow(5, 1) == 5);
    EXPECT_TRUE(FastPow(5, 2) == 25);
    EXPECT_TRUE(FastPow(5, 3) == 125);
    EXPECT_TRUE(FastPow(5, 4) == 625);
    EXPECT_TRUE(FastPow(5, 5) == 3125);
    EXPECT_TRUE(FastPow(5, 6) == 15625);
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
