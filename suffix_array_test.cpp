#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "suffix_array.hpp"

using namespace std;

TEST(SA, Naive) {
    SuffixArray sa("banana");
    vector<int> expect{5, 3, 1, 0, 4, 2};
    sa.BuildNaive();
    auto arr = sa.SA();
    for (size_t i = 0; i < 6; i++) {
        EXPECT_TRUE(arr[i] == expect[i]);
    } 
}

TEST(SA, NormalSort) {
    SuffixArray sa("banana");
    vector<int> expect{5, 3, 1, 0, 4, 2};
    // sa.BuildNormalSort();
    sa.BuildNormalSort();
    auto arr = sa.SA();
    for (size_t i = 0; i < 6; i++) {
        EXPECT_TRUE(arr[i] == expect[i]);
    } 
}

TEST(SA, RadixSort) {
    SuffixArray sa("banana");
    vector<int> expect{5, 3, 1, 0, 4, 2};
    // sa.BuildRadixSort();
    sa.BuildRadixSort();
    // sa.BuildNormalSort();
    auto arr = sa.SA();
    for (size_t i = 0; i < 6; i++) {
        EXPECT_TRUE(arr[i] == expect[i]);
    } 

    EXPECT_TRUE(sa.LCP(0, 1) == 0);
    EXPECT_TRUE(sa.LCP(1, 3) == 3);

    sa.BuildRMQ();
    EXPECT_TRUE(sa.OptLCP(0, 1) == 0);
    EXPECT_TRUE(sa.OptLCP(1, 3) == 3);
}

TEST(SA, IsSubStr) {
    string raw_str = "banana";
    SuffixArray sa(raw_str);
    sa.BuildRadixSort();
    sa.BuildRMQ();

    vector<string> x {"ban", "ana", "a", "abc", "ana", "x"};
    vector<bool> res {true, true, true, false, true, false};
    
    auto IsSubstr = [&sa, &raw_str](string s){
        auto suffix_arr = sa.SA();
        string smallest_suffix = raw_str.substr(suffix_arr[0]);
        string largest_suffix = raw_str.substr(suffix_arr[suffix_arr.size() - 1]);

        if (smallest_suffix.find(s) == string::npos && s < smallest_suffix) {
            return false;
        }
        if (largest_suffix.find(s) == string::npos && s > largest_suffix) {
            return false;
        }

        int left = 0;
        int right = suffix_arr.size() - 1;
        while(true) {
            if (left > right) break;
            int mid = (left + right) / 2;
            string middle_suffix = raw_str.substr(suffix_arr[mid]);
            if (middle_suffix.find(s) == string::npos) {
                if (s > middle_suffix) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else {
                return true;
            } 
        }
        return false;
    };

    for (size_t i = 0; i < x.size(); i++) {
        EXPECT_TRUE(IsSubstr(x[i]) == res[i]);
    }
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
