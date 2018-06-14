#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "tarjan_sparse_table.hpp"

using namespace std;

TEST(STBasic, ST) {
    IntVec A {1, 3, 2, 4, 5, 0, 6, 9, 8, 7};
    SparseTable st(A); 

    EXPECT_TRUE(st.Query(0, 0) == 1);
    EXPECT_TRUE(st.Query(9, 9) == 7);
    EXPECT_TRUE(st.Query(0, 9) == 0);
    EXPECT_TRUE(st.Query(0, 2) == 1);
    EXPECT_TRUE(st.Query(1, 3) == 2);
    EXPECT_TRUE(st.Query(3, 5) == 0);
    EXPECT_TRUE(st.Query(6, 8) == 6);
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
