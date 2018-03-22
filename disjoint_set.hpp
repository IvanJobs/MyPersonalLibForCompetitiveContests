#include <bits/stdc++.h>

class DisjointSet {
  public:
    DisjointSet() {
      under_.clear();
    }

    bool In(std::string x) {
      std::string out;
      if (Find(x, out)) return true;
      else return false;
    }

    void AddSet(std::string x) {
      std::string out;
      if (Find(x, out)) return ;

      int total_num = str2int_.size();
      str2int_[x] = total_num;
      int2str_[total_num] = x;

      under_.push_back(total_num); 
      rank_.push_back(0);
    }

    std::string Root(std::string x) {
      std::string out = "";
      Find(x, out);
      return out;  
    }

    bool Find(std::string x, std::string & out /* root representitive */) {
      if (str2int_.find(x) == str2int_.end()) return false;

      int ix = str2int_[x];
      int ox;
      if (find(ix, ox)) {
        out = int2str_[ox];
        return true; 
      } 

      return false;
    }

    void Union(std::string x, std::string y) {
      std::string xroot, yroot;
      if (Find(x, xroot) && Find(y, yroot)) {
        int xroot_idx = str2int_[xroot];
        int yroot_idx = str2int_[yroot];  

        if (xroot_idx == yroot_idx) return ;

        if (rank_[xroot_idx] > rank_[yroot_idx]) {
          under_[yroot_idx] = xroot_idx;
        } else if (rank_[yroot_idx] > rank_[xroot_idx]) {
          under_[xroot_idx] = yroot_idx;
        } else {
          under_[xroot_idx] = yroot_idx;
          rank_[yroot_idx] += 1; 
        }
      } 
    }
  private:
    // inner find using int as key.
    bool find(int x, int & out) {
      if (x >= under_.size()) return false;
      
      if (under_[x] != x) {
        int outx;
        if (find(under_[x], outx)) {
          under_[x] = outx;
          out = outx;
          return true;
        } else {
          // impossible
          return false;
        }
      } else {
        out = x;
        return true;
      }
    }
  private:
    std::vector<int> under_;
    std::vector<int> rank_;
    std::map<std::string, int> str2int_;
    std::map<int, std::string> int2str_;
};
