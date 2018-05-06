#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "treap.hpp"

using namespace std;

int GetRandomInt() {
    srand(time(nullptr));
    return rand();
}

TEST(TreapBasic, CheckBasic) {
    Treap tr;
    set<int> collect_random_ints;
    for (int i = 0; i < 100; i++) {
        int current_random = GetRandomInt();
        collect_random_ints.insert(current_random);
    }
    for (auto v: collect_random_ints) {
        tr.Insert(v);
    }

    for (auto v: collect_random_ints) {
        EXPECT_TRUE(tr.Has(v));
    }

    EXPECT_TRUE(tr.Size() == collect_random_ints.size());
    int get_one = *(collect_random_ints.begin());
    tr.Delete(get_one);
    EXPECT_FALSE(tr.Has(get_one));

    for (auto v: collect_random_ints) tr.Delete(v);
    EXPECT_TRUE(tr.Size() == 0);
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
