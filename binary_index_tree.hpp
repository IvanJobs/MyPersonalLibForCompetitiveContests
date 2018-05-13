#include <bits/stdc++.h>

using namespace std;

/**
 *  index starts from 1.
 *  we don't maintain original array here,
 *  you can maintain it outside of this FenwickTree.
 */
using INT = long long;
class FenwickTree {
    public:
        FenwickTree(int n) {
            sums_.resize(n + 1, 0);     
        }

        INT RangeSum(int l, int r) {
            if (l - 1 <= 0) return prefixSum(r);
            else {
                return prefixSum(r) - prefixSum(l - 1);
            }
        }

        void Update(int idx, INT delta) {
            sums_[idx] += delta;
            idx += lowbit(idx);
            while(true) {
                if (idx >= sums_.size()) break;
                sums_[idx] += delta;

                idx += lowbit(idx);
            }
        }
    private:
        // x >= 0
        int lowbit(int x) {
            return x & (-x); 
        }

        INT prefixSum(int i) {
            INT res = sums_[i];
            int next_idx = i - lowbit(i);
            while(true) {
                if (next_idx <= 0) break;
                res += sums_[next_idx];
                next_idx = next_idx - lowbit(next_idx);
            }
            return res;
        }

        vector<INT> sums_;
};
