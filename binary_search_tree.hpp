#include <bits/stdc++.h>

using namespace std;

struct BSTNode {
  int key_;
  int associated_value_;
};


class BinarySearchTree {
  public:
    void Insert(int key, int associated_value); // add new node by (key, associated_value).
    BSTNode * Search(int key); // search node by key.
    void Delete(int key); // delete node by key.
    bool Check(); // verification.
    void Travel(); // in order traversal.
    void Show(); // showing bst in ascii style graph.
  private:
    BSTNode * root{nullptr};
};

