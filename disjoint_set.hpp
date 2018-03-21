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

      int mapped_key = str2int_[x];
      std::string out2;
      if (under_[mapped_key] != mapped_key) {
        Find(int2str_[under_[mapped_key]], out2)
        int parent_idx = str2int_[out2];
        under_[mapped_key] = parent_idx;
      }

      out = out2;
      return true;
    }

    void Union(std::string x, std::string y) {
    
    }
  private:
    std::vector<int> under_;
    std::map<std::string, int> str2int_;
    std::map<int, std::string> int2str_;
};
