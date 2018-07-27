#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "ex_gcd.hpp"

using namespace std;

TEST(ExGCD, Basic) {
    int a, b, x, y;
    a = 12;
    b = 8;
    int g = ex_gcd(a, b, x, y);
    
    EXPECT_TRUE(g == 4);
    EXPECT_TRUE(x == 1);
    EXPECT_TRUE(y == -1);
}


int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
