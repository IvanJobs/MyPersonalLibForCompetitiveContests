#include <bits/stdc++.h>

using namespace std;
using IntVec = vector<int>;
using Matrix = vector<IntVec>;
class SparseTable {
    public:
        SparseTable(IntVec & v): v_(v) {
            buildSparseTable();
        }
        
        int Query(int i, int j) {
            int width = j - i + 1;
            int logn = static_cast<int>(log2(static_cast<double>(width)));
            int uniform_width = static_cast<int>(pow(2.0, static_cast<double>(logn))); 
            return min(sparse_table_[i][logn], sparse_table_[j - uniform_width + 1][logn]);
        }
    private:
        void buildSparseTable() {
            // prepare empty sparse_table_.
            int logn = static_cast<int>(log2(static_cast<double>(v_.size())));
            sparse_table_.clear();
            for (int i = 0; i < v_.size(); i++) {
                sparse_table_.push_back(IntVec(logn + 1));
            }

            // calculate sparse_table_[i][0] first
            for (int i = 0; i < v_.size(); i++) {
                sparse_table_[i][0] = v_[i];
            }

            // calculate sparse_table_[i][k], k > 0
            int two_k_1 = 1;
            for (int k = 1; k <= logn; k++) {
                for (int i = 0; i < v_.size(); i++ ) {
                    sparse_table_[i][k] = sparse_table_[i][k - 1];
                    if (i + two_k_1 < v_.size()) {
                        sparse_table_[i][k] = min(sparse_table_[i][k], sparse_table_[i + two_k_1][k - 1]); 
                    } 
                }
                two_k_1 *= 2;
            }
        }

        Matrix sparse_table_;
        IntVec v_;
};
