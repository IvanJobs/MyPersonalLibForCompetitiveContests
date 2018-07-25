#include <bits/stdc++.h>

using namespace std;

class Kmp {
    public:
        static int SearchFirst(string text, string pattern) {
            // build Fail arr on pattern.
            //
            vector<int> F; // idx -> value means: prefix[0...idx]'s longest common prefix/suffix.
            F.resize(pattern.size());

            F[0] = 0;
            size_t i = 1;
            while(i < F.size()) {
                // F[0...i-1] is done, we need to calculate F[i] now.
                //
                int consider_idx = i - 1;
                while(true) {
                    int len = F[consider_idx];
                    // compare pattern[len] with pattern[i]
                    if (pattern[len] == pattern[i]) {
                        F[i] = len + 1;
                        break;
                    }

                    if (len == 0) {
                        F[i] = 0;
                        break;
                    }

                    consider_idx = len - 1;
                }

                i++; 
            }

            // use Fail arr to search.
            //
            int plen = int(pattern.size());
            int tlen = int(text.size());
            int ti = 0;
            int pi = 0;
            while(ti < tlen) {
                while(text[ti] == pattern[pi] && ti < tlen && pi < plen) {
                    ti++;
                    pi++;
                }

                if (pi >= plen) {
                    // bingo, we found one.
                    //
                    return ti - plen;
                }

                if (ti >= tlen) {
                    // not found.
                    //
                    return -1;
                }
                
                if (text[ti] != pattern[pi]) {
                    // where magic happens.
                    //
                    if (pi == 0) {
                        ti++;
                    } else {
                        int common_len = F[pi - 1]; 
                        pi = common_len; 
                    }
                }
            }
            return -1;
        }
};
