#include <bits/stdc++.h>

using namespace std;
template <class Number>
class SegmentTree {
    public:
        using NumberVec = vector<Number>;
        using Range = pair<size_t, size_t>;
        bool RangeEqual(Range & lhs, Range & rhs) {
            if (lhs.first == rhs.first && lhs.second == rhs.second) {
                return true;
            } else {
                return false;
            }
        }
        
    public:
        SegmentTree(NumberVec raw):raw_(raw) {
            size_t n = raw.size();
            under_.resize(2 * n - 1);
            // cout<<"under_.size():"<<under_.size()<<endl;
            recursiveConstruct(0, make_pair(0, n - 1));
        }

        void Update(Number delta, size_t j) {
            recursiveUpdate(0, make_pair(0, raw_.size() - 1), j, delta);
            return ; 
        }

        Number Sum(size_t lhs, size_t rhs) {
            return recursiveSum(0, make_pair(0, raw_.size() - 1), make_pair(lhs, rhs));  
        }

    private:
        void recursiveUpdate(size_t i, Range r, size_t j, Number delta) {
            // cout<<"recursiveUpdate("<<i<<",("<<r.first<<","<<r.second<<"),"<<j<<","<<delta<<")"<<endl;
            // j must in [r.first, r.second].
            under_[i] += delta;

            if (r.first == r.second) {
                return ;
            }

            size_t left = r.first;
            size_t right = r.second;
            size_t mid = (left + right) / 2;

            // split [left, right] into [left, mid] and [mid + 1, right].
            //
            if (j >= left && j <= mid) {
                recursiveUpdate(2 * i + 1, make_pair(left, mid), j, delta);
            } 
            if (j >= mid + 1 && j <= right) {
                recursiveUpdate(2 * i + 2, make_pair(mid + 1, right), j, delta);
            }
        }
        /**
         * tr is in sr. 
         */
        Number recursiveSum(size_t i, Range sr, Range tr) {
            // cout<<"recursiveSum("<<i<<",("<<sr.first<<","<<sr.second<<"),("<<tr.first<<","<<tr.second<<"))"<<endl;
            if (RangeEqual(sr, tr)) {
                return under_[i];
            } 

            size_t left = sr.first;
            size_t right = sr.second;
            size_t mid = (left + right) / 2;

            // split [left, right] to [left, mid] and [mid + 1, right]. 
            //
            if (mid < tr.first) {
                return recursiveSum(2 * i + 2, make_pair(mid + 1, right), tr); 
            } else if (mid > tr.second) {
                return recursiveSum(2 * i + 1, make_pair(left, mid), tr); 
            } else {
                Number left_res = recursiveSum(2 * i + 1, make_pair(left, mid),  make_pair(tr.first, mid));
                Number right_res = 0;
                if (mid + 1 <= tr.second) {
                    right_res = recursiveSum(2 * i + 2, make_pair(mid + 1, right), make_pair(mid + 1, tr.second));
                }

                return left_res + right_res;
            }
        }
        /*
         * (0, 0, raw_.size() - 1,) 
         */
        Number recursiveConstruct(size_t i, Range r) {
            // cout<<"recursiveConstruct("<<i<<",("<<r.first<<","<<r.second<<")"<<endl;
            if (r.first == r.second) {
                under_[i] = raw_[r.first];
                return under_[i];
            } 

            size_t left = r.first;
            size_t right = r.second;
            // split [left, right]
            size_t mid = (left + right) / 2;
            // [left, mid], [mid + 1, right]
            Number left_res = recursiveConstruct(2 * i + 1, make_pair(left, mid));
            Number right_res = recursiveConstruct(2 * i + 2, make_pair(mid + 1, right));

            Number final_res = left_res + right_res;
            under_[i] = final_res;
            return under_[i];
        }        

        NumberVec under_{};
        NumberVec raw_;
};
