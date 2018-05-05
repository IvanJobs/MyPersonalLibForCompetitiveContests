#ifndef TRIE_HPP_
#define TRIE_HPP_
#include <bits/stdc++.h>

using namespace std;
#define BRANCH_NUM 26
struct DummyNode {
  DummyNode() {
    for (int i = 0; i < BRANCH_NUM; i++) {
      children_[i] = nullptr;
    }

  }
  char c_{'A'};
  bool final_{false};
  struct DummyNode * children_[BRANCH_NUM]; 
};
using TrieNode = struct DummyNode;
class Trie {
  public:
    Trie() {
      flat_nodes_.push_back(TrieNode());
      root_ = &flat_nodes_[flat_nodes_.size() - 1];
    }
    // insert a string
    void Insert(const string & s) {
      if (s == "") return ;

      TrieNode * curr = root_;
      for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        int idx = c - 'a';
        TrieNode * new_node = nullptr;
        
        if (curr->children_[idx] == nullptr) {
          new_node = newTrieNode();
          new_node->c_ = c;
          curr->children_[idx] = new_node;
        }

        if (i == s.size() - 1) {
          new_node->final_ = true;
        }
        curr = new_node;
      }  
    }
    bool Has(const string & s) {
        if (s == "") return true;

        TrieNode * curr = root_;
        for (size_t i = 0; i < s.size(); i++) {
            int idx = s[i] - 'a';
            if (curr->children_[idx] == nullptr) return false;

            curr = curr->children_[idx];
            if (i == s.size() - 1 && curr->final_ == false) {
                return false;
            }
        }
        return true;
    } 

  private:
    TrieNode * newTrieNode() {
      flat_nodes_.push_back(TrieNode());
      return &flat_nodes_[flat_nodes_.size() - 1];
    }
  private:
    TrieNode * root_{nullptr};
    vector<TrieNode> flat_nodes_;
};
#endif
