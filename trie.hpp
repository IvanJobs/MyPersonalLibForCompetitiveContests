#include <bits/stdc++.h>

using namespace std;

struct TrieNode {
  TrieNode() {
    children_.clear();
    children_.resize(26, nullptr); 
  }
  
  bool leaf_{true}; 
  vector<struct TrieNode *> children_; 
};

class StringTrie {
  public:
    // insert a string
    void Insert(const string & s);
    bool Search(const string & s); 
};
