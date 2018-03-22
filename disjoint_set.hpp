#include <bits/stdc++.h>

class DisjointSet {
  public:
    DisjointSet() {
      under_.clear();
    }

    void AddSet(std::string x) {
      std::string out;
      if (Find(x, out)) return ;

      int total_num = str2int_.size();
      str2int_[x] = total_num;
      int2str_[total_num] = x;

      under_.push_back(total_num); 
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
    
    }
  private:
    // inner find using int as key.
    bool find(int x, int & out) {
      if (x >= under_.size()) return false;
      
      if (under_[x] != x) {
        int outx;
        if (find(under_[x], outx)) {
          under_[x] = outx;
        } else {
          // impossible
          return false;
        }
      }

      return x;
    }
  private:
    std::vector<int> under_;
    std::map<std::string, int> str2int_;
    std::map<int, std::string> int2str_;
};
