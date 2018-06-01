#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "kmp.hpp"

using namespace std;

TEST(Kmp, Kmp) {
    EXPECT_TRUE(Kmp::SearchFirst("1234123", "341") == 2);
    EXPECT_TRUE(Kmp::SearchFirst("1234123", "345") == -1);
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
