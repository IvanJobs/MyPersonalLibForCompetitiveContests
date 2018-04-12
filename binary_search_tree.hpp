#include <bits/stdc++.h>

using namespace std;

struct BSTNode {
  BSTNode(int key, int associated_value): key_(key), associated_value_(associated_value) {}
  int key_;
  int associated_value_;

  struct BSTNode * left{nullptr};
  struct BSTNode * right{nullptr};
};


class BinarySearchTree {
  public:
    ~BinarySearchTree();
    void Insert(int key, int associated_value); // add new node by (key, associated_value).
    struct BSTNode * Search(int key); // search node by key.
    void Delete(int key); // delete node by key.
    bool Check(); // verification.
    void Travel(); // in order traversal.
    void Show(); // showing bst in ascii style graph.
  private:
    void releaseNodes(struct BSTNode * p_curr);
    struct BSTNode * root{nullptr};
};

// because nodes are allocated on heap, so we need to manually release nodes' space.
void BinarySearchTree::releaseNodes(struct BSTNode * p_curr) {
  // release sub trees, and then release self.
  
  // base case: left == nullptr && right == nullptr.
  if (p_curr->left == nullptr && p_curr->right == nullptr) {
    return ;
  } 

  if (p_curr->left != nullptr) {
    releaseNodes(p_curr->left); 
  }

  if (p_curr->right != nullptr) {
    releaseNodes(p_curr->right); 
  }

  delete p_curr;
  p_curr = nullptr; 
}

BinarySearchTree::~BinarySearchTree() {
  releaseNodes(root);
}

void BinarySearchTree::Insert(int key, int associated_value) {
  // if root == nullptr, allocate a node and point it with root.
  // else we can find a node with binary search style, 
  // and allocate a node, point it with its left or right.
  //
  struct BSTNode * p_new = new BSTNode(key, associated_value); // anyway, we need to allocate a node.
  if (root == nullptr) {
    root = p_new; 
    return ;
  } 

  struct BSTNode * p_curr = root;
  bool put_left = false;
  while(true) {
    if (key <= p_curr->key_) {
      // pending to left 
      if (p_curr->left == nullptr) {
        put_left = true;
        break;
      }

      p_curr = p_curr->left;
    } else {
      // pending to right 
      if (p_curr->right == nullptr) {
        put_left = false;
        break;
      }

      p_curr = p_curr->right;
    }
  }

  if (put_left) {
    p_curr->left = p_new;
  } else {
    p_curr->right = p_new;
  }
}

BSTNode * BinarySearchTree::Search(int key) {

  struct BSTNode * p_curr = root;
  while (p_curr != nullptr) {
    if (key == p_curr->key_) {
      return p_curr; 
    } else if (key < p_curr->key_) {
      p_curr = p_curr->left; 
    } else {
      p_curr = p_curr->right; 
    }
  }

  return nullptr;
}

void BinarySearchTree::Delete(int key) {

}

bool BinarySearchTree::Check() {

}

void BinarySearchTree::Travel() {

}

void BinarySearchTree::Show() {
  queue<struct BSTNode*> q;
  while(q.empty() == false) {
    struct BSTNode * curr = q.front();
    q.pop();

    cout<<curr->key_<<"->";
    if (curr->left != nullptr) {
      q.push(curr->left);
      cout<<curr->left->key_<<",";
    }
    if (curr->right != nullptr) {
      q.push(curr->right);
      cout<<curr->right->key_<<",";
    }
    cout<<endl;
  } 
}
