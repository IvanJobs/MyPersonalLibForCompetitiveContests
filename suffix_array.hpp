#include <bits/stdc++.h>

using namespace std;

class SuffixArray {
    public:
        SuffixArray(string s) {
            s_ = s;
            sa_.resize(s_.size());
        }

        vector<int> & SA() {
            return sa_;
        } 

        void BuildNaive() {
            using SuffixIndex = tuple<string, int>;
            vector<SuffixIndex> v;
            for (int i = 0; i < s_.size(); i++) {
                v.push_back(make_tuple(s_.substr(i), i));
            } 

            auto cmp = [](SuffixIndex previous, SuffixIndex following) {
                if (get<0>(previous) < get<0>(following)) {
                    return true;
                } else return false;
            };

            sort(v.begin(), v.end(), cmp);
            for (size_t i = 0; i < v.size(); i++) {
                sa_[i] = get<1>(v[i]);
            }
        }

        void BuildNormalSort() {
            using InitSortItem = tuple<char, int>;
            // sort by first char
            vector<InitSortItem> v;
            for (int i = 0; i < s_.size(); i++) {
                v.push_back(make_tuple(s_[i], i));
            }
            auto cmp = [](InitSortItem a, InitSortItem b) {
                if (get<0>(a) < get<0>(b)) {
                    return true;
                } else return false;
            };

            sort(v.begin(), v.end(), cmp);
            map<int, int> rank_map; // make rank_map
            rank_map[get<1>(v[0])] = 0;
            for (int i = 1; i < v.size(); i++) {
                int previous_idx = get<1>(v[i - 1]);
                int current_idx = get<1>(v[i]);
                if (s_[previous_idx] == s_[current_idx]) {
                    rank_map[current_idx] = rank_map[previous_idx];
                } else {
                    rank_map[current_idx] = rank_map[previous_idx] + 1;
                }
            }

            using SortTupleItem = tuple<int, int, int, int>; // suffix_idx, rank0, rank1, width.
            vector<SortTupleItem> vec;
            { //prepare initial state
                for (int i = 0; i < v.size(); i++) {
                    int suffix_idx = get<1>(v[i]);
                    int rank0 = rank_map[suffix_idx];
                    int w = 1;
                    int rank1 = -1;
                    if (suffix_idx + w < v.size())
                        rank1 = rank_map[suffix_idx + w];
                    vec.push_back(make_tuple(suffix_idx, rank0, rank1, w));        
                }        
            }

            { // loop until w >= s_.size();
                auto rank_cmp = [](SortTupleItem a, SortTupleItem b) {
                    if (get<1>(a) < get<1>(b)) return true;
                    else if (get<1>(a) > get<1>(b)) return false;
                    else {
                        if (get<2>(a) < get<2>(b)) return true;
                        else return false;
                    }
                };

                int w = 1;
                int target_size = int(s_.size());
                while (w <= target_size) {
                    // sort vec by (rank0, rank1) 
                    sort(vec.begin(), vec.end(), rank_cmp);
                    
                    { // update rankings. (suffix_idx, rank0, rank1, width)
                        rank_map[get<0>(vec[0])] = 0;
                        for (int i = 1; i < vec.size(); i++) {
                            int prev_idx = get<0>(vec[i - 1]);
                            int prev_rank0 = get<1>(vec[i - 1]);
                            int prev_rank1 = get<2>(vec[i - 1]);
                            int curr_idx = get<0>(vec[i]);
                            int curr_rank0 = get<1>(vec[i]);
                            int curr_rank1 = get<2>(vec[i]);

                            if (prev_rank0 == curr_rank0 && prev_rank1 == curr_rank1) {
                                rank_map[curr_idx] = rank_map[prev_idx];
                            } else {
                                rank_map[curr_idx] = rank_map[prev_idx] + 1;
                            }
                        }

                        for (int i = 0; i < vec.size(); i++) {
                            int curr_idx = get<0>(vec[i]);
                            w = get<3>(vec[i]);
                            w *= 2;
                            get<3>(vec[i]) = w;
                            get<1>(vec[i]) = rank_map[curr_idx];
                            int rank1 = -1;
                            if (curr_idx + w < vec.size()) {
                                rank1 = rank_map[curr_idx + w];
                            }
                            get<2>(vec[i]) = rank1;
                        }
                    }
                }

                // done, make sa_ from vec
                for (size_t i = 0; i < vec.size(); i++) {
                    sa_[i] = get<0>(vec[i]);
                }
            }
        }

        void BuildRadixSort() {
        
        }

    private:
        string s_;
        vector<int> sa_;
};
