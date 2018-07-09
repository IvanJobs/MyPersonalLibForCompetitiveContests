#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "segment_tree.hpp"

using namespace std;

TEST(SegmentTree, Basic) {
    vector<int> test_arr {1, 3, 2, 5, 4, 0};
    SegmentTree<int> st(test_arr);
    
    EXPECT_TRUE(st.Sum(0, 0) == 1);
    EXPECT_TRUE(st.Sum(0, 1) == 4);
    EXPECT_TRUE(st.Sum(0, 2) == 6);
    EXPECT_TRUE(st.Sum(0, 3) == 11);
    EXPECT_TRUE(st.Sum(0, 4) == 15);
    EXPECT_TRUE(st.Sum(0, 5) == 15);

    for (size_t i = 0; i < test_arr.size(); i++) {
        for (size_t j = i; j < test_arr.size(); j++) {
            int s = 0;
            for (size_t k = i; k <= j; k++) s += test_arr[k];
            EXPECT_TRUE(st.Sum(i, j) == s); 
        }
    }
}

TEST(SegmentTree, Update) {
    vector<int> test_arr(10);
    for (size_t i = 0; i < test_arr.size(); i++) {
        test_arr[i] = rand() % 100;
    }
    SegmentTree<int> st(test_arr);

    for (size_t i = 0; i < test_arr.size(); i++) {
        for (size_t j = i; j < test_arr.size(); j++) {
            int s = 0;
            for (size_t k = i; k <= j; k++) s += test_arr[k];
            EXPECT_TRUE(st.Sum(i, j) == s); 
        }
    }

    for (size_t i = 0; i < test_arr.size(); i++) {
        // st.Update((rand() % 100) - test_arr[i], i);
    }

    for (size_t i = 0; i < test_arr.size(); i++) {
        for (size_t j = i; j < test_arr.size(); j++) {
            int s = 0;
            for (size_t k = i; k <= j; k++) s += test_arr[k];
            EXPECT_TRUE(st.Sum(i, j) == s); 
        }
    }
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
