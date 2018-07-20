#include <bits/stdc++.h>
#include "tarjan_sparse_table.hpp"
using namespace std;

using SortTupleItem = tuple<int, int, int, int>; // suffix_idx, rank0, rank1, width.
using IntVec = vector<int>;
using IntMatrix = vector<IntVec>;

class SuffixArray {
    public:
        SuffixArray(string s) {
            s_ = s;
            sa_.resize(s_.size());
        }

        vector<int> & SA() {
            return sa_;
        } 

        // build rmq for lcp(i, j).
        void BuildRMQ() {
            // what we got here?
            // array sa_ and function LCP
            //
            // what does sa_ tell us?
            // suffix sa_[i] is in position i.
            //
            map<int, int> suffix_orders;
            for (int i = 0; i < sa_.size(); i++) suffix_orders[sa_[i]] = i;
            // what does suffix_orders tell us? 
            // what the order index of a specific suffix index?
            //
            vector<int> v; v.clear();
            for (size_t i = 1; i < sa_.size(); i++) {
                v.push_back(LCP(sa_[i - 1], sa_[i])); 
            }

            sparse_table_ = std::make_shared<SparseTable>(v);
        }

        // i, j are suffix_array's indexes.
        int OptLCP(int i, int j) {
            // make sure i < j
            if (i > j) {
                swap(i, j);
            }
            return sparse_table_->Query(i, j - 1);
        }

        // return length of Longest Common Prefix(A[i...], A[j...]).
        int LCP(int i, int j) {
            // logn, using rank_.
            //
            int res = 0;
            while(true){
                if (i >= rank_.size() || j >= rank_.size()) break;

                int k = 0;
                int over2 = 1;
                int w = 0;
                while(k < rank_[0].size() && rank_[i][k] == rank_[j][k]) {
                    w = over2;
                    k++;
                    over2 *= 2;
                }

                if (k == 0) break;

                res += w; 
                i += w;
                j += w;
            }

            return res;
        }

        void BuildNaive() {
            // bind suffix string with its starting index, then do sorting as a whole part.
            using SuffixIndex = tuple<string, int>;
            vector<SuffixIndex> v;
            // prepare SuffixIndex vector.
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

            // Rank[i][k]: starts from index i, width 2^k, stores its rank.
            //  0 <= i <= v.size() - 1, 0 <= k <= log2(v.size())
            int logn = static_cast<int>(log2(static_cast<double>(v.size())));
            logn += 1; // because we want rank_[i][k] to cover the whole array sized with v.size().

            // init Rank.
            rank_.clear();
            for (int i = 0; i < v.size(); i++) {
                rank_.push_back(IntVec(1 + logn)); // 0 1 2 ... logn
            }

            // prepare Rank[i][0]
            rank_[get<1>(v[0])][0] = 1;
            for (int i = 1; i < v.size(); i++) {
                if (get<0>(v[i]) == get<0>(v[i - 1])) {
                    rank_[get<1>(v[i])][0] = rank_[get<1>(v[i - 1])][0];
                } else {
                    rank_[get<1>(v[i])][0] = rank_[get<1>(v[i - 1])][0] + 1;
                }
            } // finish Rank[i][0]

            int last_w = 1;
            vector<SortTupleItem> vec_to_sort;
            for (int k = 1; k <= logn; k++) {
                // work with Rank[i][k]
                vec_to_sort.clear();
                for (int i = 0; i < v.size(); i++) {
                    int rank0 = rank_[i][k - 1];
                    int shift_idx = i + last_w;
                    int rank1 = 0; // big question mark here!!!!!!
                    if (shift_idx < v.size()) {
                        rank1 = rank_[shift_idx][k - 1];
                    }
                    int suffix_idx = i;
                    int w = last_w * 2; // seems no need to take width in the tuple.

                    vec_to_sort.push_back(make_tuple(suffix_idx, rank0, rank1, w)); 
                }

                // sort vec_to_sort
                {
                    // prepare compare function.
                    auto cmp_by_ranks = [](const SortTupleItem & a, const SortTupleItem & b) {
                        int rank0a = get<1>(a);  
                        int rank1a = get<2>(a);  
                        int rank0b = get<1>(b);
                        int rank1b = get<2>(b);

                        if (rank0a < rank0b) return true;
                        else if (rank0a > rank0b) return false;
                        else {
                            if (rank1a < rank1b) return true;
                            else return false;
                        }
                    };

                    sort(vec_to_sort.begin(), vec_to_sort.end(), cmp_by_ranks);
                }

                // update rank_[i][k]
                {
                    rank_[get<0>(vec_to_sort[0])][k] = 1;
                    for (int i = 1; i < vec_to_sort.size(); i++) {
                        if (get<1>(vec_to_sort[i])  == get<1>(vec_to_sort[i - 1]) &&
                            get<2>(vec_to_sort[i]) == get<2>(vec_to_sort[i - 1])) {
                            rank_[get<0>(vec_to_sort[i])][k] = rank_[get<0>(vec_to_sort[i - 1])][k];
                        } else {
                            rank_[get<0>(vec_to_sort[i])][k] = rank_[get<0>(vec_to_sort[i - 1])][k] + 1;
                        }
                    }
                }
               
                last_w *= 2;
            }  

            // final results must be in rank_[i][logn].
            for (int i = 0; i < s_.size(); i++) {
                sa_[rank_[i][logn] - 1] = i; 
            } 
        }
        // suffix_idx, rank0, rank1, w
        // just use rank1 to do sorting.
        void RadixSort(vector<SortTupleItem> & vec) {
            // sort vec by radix sorting.  
            // sort by rank1 first, then sort by rank0
            vector<int> buckets; // radix -> cnt
            buckets.resize(vec.size() + 1); // because may have 0 for rank1.
            for (int i = 0; i < buckets.size(); i++) buckets[i] = 0; // init
            
            { // fill buckets
                for (int i = 0; i < vec.size(); i++) {
                    int rank1 = get<2>(vec[i]);
                    buckets[rank1]++;
                }
            }

            { // accumulate buckets

                for (int i = 1; i < buckets.size(); i++) {
                    
                    buckets[i] += buckets[i - 1];
                }
            }

            vector<SortTupleItem> to_vec;
            to_vec.resize(vec.size());
            { // sort using buckets
                for (int i = vec.size() - 1; i >= 0; i--) {
                    int rank1 = get<2>(vec[i]);
                    to_vec[buckets[rank1] - 1] = vec[i];
                    buckets[rank1]--;
                }  
            }

            // copy to_vec to vec.
            for (int i = 0; i < vec.size(); i++) {
                vec[i] = to_vec[i];
            }

            // sort by rank0
            for (int i = 0; i < buckets.size(); i++) buckets[i] = 0; // init
            
            { // fill buckets
                for (int i = 0; i < vec.size(); i++) {
                    int rank0 = get<1>(vec[i]);
                    buckets[rank0]++;
                }
            }

            { // accumulate buckets
                for (int i = 1; i < buckets.size(); i++) {
                    
                    buckets[i] += buckets[i - 1];
                }
            }

            { // sort using buckets
                for (int i = vec.size() - 1; i >= 0; i--) {
                    int rank0 = get<1>(vec[i]);
                    to_vec[buckets[rank0] - 1] = vec[i];
                    buckets[rank0]--;
                }  
            }

            // copy to_vec to vec.
            for (int i = 0; i < vec.size(); i++) {
                vec[i] = to_vec[i];
            }

        }

        void BuildRadixSort() {
            using InitSortItem = tuple<char, int>;
            // sort by first char
            vector<InitSortItem> v;
            v.clear();
            for (int i = 0; i < s_.size(); i++) {
                v.push_back(make_tuple(s_[i], i));
            }
            
            auto cmp = [](InitSortItem a, InitSortItem b) {
                if (get<0>(a) < get<0>(b)) {
                    return true;
                } else return false;
            };
            sort(v.begin(), v.end(), cmp);

            // Rank[i][k]: starts from index i, width 2^k, stores its rank.
            //  0 <= i <= v.size() - 1, 0 <= k <= log2(v.size())
            int logn = static_cast<int>(log2(static_cast<double>(v.size())));
            logn += 1; // because we want rank_[i][k] to cover the whole array sized with v.size().

            // init Rank.
            rank_.clear();
            for (int i = 0; i < v.size(); i++) {
                rank_.push_back(IntVec(1 + logn)); // 0 1 2 ... logn
            }

            // prepare Rank[i][0]
            rank_[get<1>(v[0])][0] = 1;
            for (int i = 1; i < v.size(); i++) {
                if (get<0>(v[i]) == get<0>(v[i - 1])) {
                    rank_[get<1>(v[i])][0] = rank_[get<1>(v[i - 1])][0];
                } else {
                    rank_[get<1>(v[i])][0] = rank_[get<1>(v[i - 1])][0] + 1;
                }
            } // finish Rank[i][0]

            int last_w = 1;
            vector<SortTupleItem> vec_to_sort;
            for (int k = 1; k <= logn; k++) {
                // work with Rank[i][k]
                vec_to_sort.clear();
                for (int i = 0; i < v.size(); i++) {
                    int rank0 = rank_[i][k - 1];
                    int shift_idx = i + last_w;
                    int rank1 = 0; // big question mark here!!!!!!
                    if (shift_idx < v.size()) {
                        rank1 = rank_[shift_idx][k - 1];
                    }
                    int suffix_idx = i;
                    int w = last_w; // seems no need to take width in the tuple.
                    vec_to_sort.push_back(make_tuple(suffix_idx, rank0, rank1, w)); 
                }

                // sort vec_to_sort
                {
                    RadixSort(vec_to_sort);
                }

                // update rank_[i][k]
                {
                    rank_[get<0>(vec_to_sort[0])][k] = 1;
                    for (int i = 1; i < vec_to_sort.size(); i++) {
                        if (get<1>(vec_to_sort[i])  == get<1>(vec_to_sort[i - 1]) &&
                            get<2>(vec_to_sort[i]) == get<2>(vec_to_sort[i - 1])) {
                            rank_[get<0>(vec_to_sort[i])][k] = rank_[get<0>(vec_to_sort[i - 1])][k];
                        } else {
                            rank_[get<0>(vec_to_sort[i])][k] = rank_[get<0>(vec_to_sort[i - 1])][k] + 1;
                        }
                    }
                }
               
                last_w *= 2;
            }  

            // final results must be in rank_[i][logn].
            for (int i = 0; i < s_.size(); i++) {
                sa_[rank_[i][logn] - 1] = i; 
            } 
        }

    private:
        string s_;
        vector<int> sa_;
        IntMatrix rank_;
        SparseTablePtr sparse_table_; 
};
