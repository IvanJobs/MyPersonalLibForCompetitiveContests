#include <gtest/gtest.h>
#include <bits/stdc++.h>

#include "interval_tree.hpp"

using namespace std;

TEST(IntervalTreeTest, Basic) {
    IntervalTree t;
    int Intervals[10][2] = {
        {1, 3},{2, 4},{3, 9},{4, 7},{5, 10},
        {7, 7},{9, 10},{2, 8},{6, 9},{7, 15}
    };

    for (int i = 0; i < 10; i++) {
        t.Insert(Intervals[i][0], Intervals[i][1]);
    }

    int QueryIntervals[10][2] = {
        {3, 6}, {4, 4}, {1, 100}, {10, 10}, {0, 0},
        {6, 6}, {8, 9}, {20, 30}, {14, 16}, {15, 17}
    };
    bool expects[10] = { 
        true, true, true, true, false,
        true, true, false, true, true 
    };

    for (int i = 0; i < 10; i++) {
        bool curr = t.AnyOverlapping(QueryIntervals[i][0], QueryIntervals[i][1]); 
        EXPECT_TRUE(curr == expects[i]);
    }
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
