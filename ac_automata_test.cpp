#include <gtest/gtest.h>
#include <bits/stdc++.h>

#include "ac_automata.hpp"

using namespace std;

TEST(AC, IsMatch) {
    vector<string> patterns {"he", "she", "his", "hers"};
    string match_text = "shers";
    string unmatch_text = "abcd";

    ACAutoMeta ac;
    for (auto s: patterns) ac.AddPatternStr(s);
    
    EXPECT_TRUE(ac.IsMatch(match_text) == true);
    EXPECT_TRUE(ac.IsMatch(unmatch_text) == true);
}

TEST(AC, Match) {
    vector<string> patterns {"he", "she", "his", "hers"};
    string text = "hehis";
    
    ACAutoMeta ac;
    for (auto s: patterns) ac.AddPatternStr(s);

    MatchResults res = ac.Match(text);
    
    EXPECT_TRUE(res.size() == 2);
    if (res.size() == 2) {
        EXPECT_TRUE(get<0>(res[0]) == 0);
        EXPECT_TRUE(get<1>(res[0]) == "he");
        EXPECT_TRUE(get<0>(res[1]) == 2);
        EXPECT_TRUE(get<1>(res[1]) == "his");
    }
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
