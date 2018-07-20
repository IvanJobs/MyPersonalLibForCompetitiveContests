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
    /*
     a
     ana
     anana
     banana
     na
     nana
     * */
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
    EXPECT_TRUE(sa.OptLCP(0, 1) == 1);
    EXPECT_TRUE(sa.OptLCP(1, 3) == 0);
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

TEST(SA, MatchAllSubstrs) {
    string raw_str = "banana";
    SuffixArray sa(raw_str);
    sa.BuildRadixSort();
    sa.BuildRMQ();
    auto suffix_arr = sa.SA();

    string p = "a";

    auto LeftMostSubstr = [&sa, &raw_str](string x) {
        auto suffix_arr = sa.SA();
        string smallest_suffix = raw_str.substr(suffix_arr[0]);
        string largest_suffix = raw_str.substr(suffix_arr[suffix_arr.size() - 1]);

        if (smallest_suffix.find(x) == string::npos && x < smallest_suffix) return -1;
        if (largest_suffix.find(x) == string::npos && x > largest_suffix) return -1;

        int left = 0;
        int right = suffix_arr.size() - 1;

        while(true) {
            int mid = (left + right) / 2;
            string middle_suffix = raw_str.substr(suffix_arr[mid]);
            if (middle_suffix.find(x) == string::npos) {
                if (x > middle_suffix) {
                    left = mid + 1; 
                } else { // x < middle_suffix
                    right = mid - 1; 
                } 
            } else {
                if (middle_suffix.find(x) == 0) {
                    right = mid; 
                } else {
                    if (x > middle_suffix) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
            }
            
            if (left >= right) break;
        }

        if (left == right) {
            return left;    
        } else {
            return -1; 
        }

    };

    auto RightMostSubstr = [&sa, &raw_str](string x) {
        auto suffix_arr = sa.SA();
        string smallest_suffix = raw_str.substr(suffix_arr[0]);
        string largest_suffix = raw_str.substr(suffix_arr[suffix_arr.size() - 1]);

        if (smallest_suffix.find(x) == string::npos && x < smallest_suffix) return -1;
        if (largest_suffix.find(x) == string::npos && x > largest_suffix) return -1;

        int left = 0;
        int right = suffix_arr.size() - 1;
        while(true) {
            int mid = (left + right) / 2;
            string middle_suffix = raw_str.substr(suffix_arr[mid]);
            if (middle_suffix.find(x) == string::npos) {
                if (x > middle_suffix) {
                    left = mid + 1;   
                } else { // x < middle_suffix.
                    right = mid - 1; 
                }
            } else {
               if (middle_suffix.find(x) == 0) {
                    left = mid;
               } else {
                    if (x > middle_suffix) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
               }
            }
            if (left >= right) break;
        }
        if (left == right) {
            return left;
        } else {
            return -1;
        }
    };
    EXPECT_TRUE(suffix_arr[LeftMostSubstr(p)] == 5);
    EXPECT_TRUE(suffix_arr[RightMostSubstr(p)] == 1);
    EXPECT_TRUE(RightMostSubstr(p) - LeftMostSubstr(p) + 1 == 3);
}

TEST(SA, LongestRepeatedSubstr) {
    string raw_str = "banana";
    SuffixArray sa(raw_str);
    sa.BuildRadixSort();
    sa.BuildRMQ();

    using Result = tuple<int, string>;
    auto LRS = [&sa, &raw_str](){
        auto suffix_arr = sa.SA();
        int i = 1;
        int res_i = -1;
        int res_cnt = -1;
        while(i < suffix_arr.size()) {
            int curr_cnt = sa.LCP(suffix_arr[i - 1], suffix_arr[i]);
            if (curr_cnt > res_cnt) {
                res_i = i;
                res_cnt = curr_cnt;
            }
            i++;
        }

        return make_tuple(res_cnt, raw_str.substr(suffix_arr[res_i], res_cnt));
    };

    Result res = LRS();
    EXPECT_TRUE(get<0>(res) == 3);
    EXPECT_TRUE(get<1>(res) == "ana");
}

TEST(SA, LongestCommonSubstr) {
    auto LCS = [](string s1, string s2){
        string s = s1 + "$" + s2;

        SuffixArray sa(s);
        sa.BuildRadixSort();
        sa.BuildRMQ();
        
        int res = 0;
        int res_i = -1;
        for (size_t i = 1; i < s.size(); i++) {
            int tmp = sa.OptLCP(i - 1, i); 
            int x = sa.SA()[i - 1];
            int y = sa.SA()[i];
            if (x > y) swap(x, y);
            
            if (x < s1.size() && y >= s1.size() + 1 && tmp > res) {
                res = tmp;
                res_i = i;
            }
        } 
        // cout<<s.substr(sa.SA()[res_i - 1])<<endl;
        // cout<<s.substr(sa.SA()[res_i])<<endl;
        return res;
    };
    // cout<<LCS("banana", "japan")<<endl;
    EXPECT_TRUE(LCS("banana", "japan") == 2);
    EXPECT_TRUE(LCS("banana", "banana") == 6);
    EXPECT_TRUE(LCS("banana", "bananb") == 5);
    EXPECT_TRUE(LCS("abanana", "bbanana") == 6);
}

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
