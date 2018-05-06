#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "trie.hpp"

using namespace std;

TEST(TrieBasic, CheckHas) {
    Trie t;
    vector<string> v {"hello", "world"};
    for (auto s: v) t.Insert(s);

    EXPECT_TRUE(t.Has("hello"));
    EXPECT_FALSE(t.Has("hel"));
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
