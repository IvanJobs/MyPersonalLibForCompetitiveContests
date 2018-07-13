#include <gtest/gtest.h>
#include <bits/stdc++.h>

#include "ac_automata.hpp"

using namespace std;

TEST(AC, IsMatch) {
    // vector<string> patterns {"he", "she", "his", "hers"};
    vector<string> patterns {"he", "she"};
    string match_text = "shers";
    string unmatch_text = "abcd";

    ACAutoMeta ac;
    for (auto s: patterns) ac.AddPatternStr(s);
    ac.Build();

    EXPECT_TRUE(ac.IsMatch(match_text) == true);
    EXPECT_TRUE(ac.IsMatch(unmatch_text) == false);
}


int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
