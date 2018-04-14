#include <bits/stdc++.h>

using namespace std;

struct BSTNode {
  BSTNode(int key, int associated_value): key_(key), associated_value_(associated_value), max_(key), min_(key) {
  }
  int key_;
  int associated_value_;
  int max_;
  int min_;

  struct BSTNode * left{nullptr};
  struct BSTNode * right{nullptr};
  struct BSTNode * parent{nullptr};
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
    void Hack();
  private:
    void releaseNodes(struct BSTNode * p_curr);
    void dfs(struct BSTNode * curr);
    void fillMinMax(struct BSTNode * curr);
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
  p_new->parent = p_curr;
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
  // if not found key, just return
  // if find key with no children, just delete it;
  // if find key with one child, delete it and replace it with the child.
  // if find key with two children, find largest in left tree, 
  // or find smallest in right tree, replace and delete.
  //

  struct BSTNode * curr = root;

  while(true) {
    if (curr == nullptr) return ;
    if (key == curr->key_) {
      break;  
    } else if (key < curr->key_) {
      curr = curr->left;
    } else { // key > curr->key_
      curr = curr->right; 
    }
  }

  // if comes here, curr->key_ == key
  if (curr->left == nullptr && curr->right == nullptr) {
    // delete curr?
    if (curr->parent == nullptr) { // root
      delete curr;
      root = nullptr; 
    } else { 
      if (curr->parent->left == curr) {
        curr->parent->left = nullptr;
        delete curr;
      } else {
        curr->parent->right = nullptr;
        delete curr; 
      } 
    } 
  } else if (curr->left == nullptr && curr->right != nullptr) {
    if (curr->parent == nullptr) { // root
      root = curr->right;
    } else {
      if (curr->parent->left == curr) {
        curr->parent->left = curr->right; 
      } else { // curr->parent->right == curr
        curr->parent->right = curr->right; 
      } 
    } 
    delete curr;
  } else if (curr->left != nullptr && curr->right == nullptr) {
    if (curr->parent == nullptr) { // root
      root = curr->left;
    } else {
      if (curr->parent->left == curr) { // left
        curr->parent->left = curr->left; 
      } else { // right
        curr->parent->right = curr->left;
      }
    }
    delete curr;
  } else { // curr->left != nullptr && curr->right != nullptr
    // find smallest in right subtree.
    struct BSTNode * to_be_found = curr->right;
    while(to_be_found->left != nullptr) to_be_found = to_be_found->left;
    
    // replace curr with to_be_found.
    curr->key_ = to_be_found->key_;
    curr->associated_value_ = to_be_found->associated_value_;
    
    // to delete to_be_found.
    if (to_be_found->right == nullptr) { 
    // to_be_found is a leaf node
      if (to_be_found->parent->left == to_be_found) {
        to_be_found->parent->left = nullptr; 
      } else {
        to_be_found->parent->right = nullptr; 
      } 
    } else {
      if (to_be_found->parent->left == to_be_found) {
        to_be_found->parent->left = to_be_found->right;
      } else {
        to_be_found->parent->right = to_be_found->right;
      }
    }

    delete to_be_found;
  }
}

bool BinarySearchTree::Check() {
  if (root == nullptr) return true;
  // fillMinMax first
  fillMinMax(root);
  
  // bfs all nodes, and check if curr->key_ >= curr->left->max_
  // and curr->key_ < curr->right->min_
  queue<struct BSTNode *> q;
  q.push(root);  
  while(q.empty() == false) {
    struct BSTNode * curr = q.front();
    q.pop();

    if (curr->left != nullptr &&
        curr->key_ < curr->left->max_) {
      return false;
    }
    if (curr->right != nullptr &&
        curr->key_ > curr->right->min_) {
      return false;
    }

    if (curr->left != nullptr) {
      q.push(curr->left);
    }
    if (curr->right != nullptr) {
      q.push(curr->right);
    }
  }

  return true;
}

void BinarySearchTree::Travel() {
  dfs(root); 
  cout<<endl;
}

void BinarySearchTree::Show() {
  queue<struct BSTNode*> q;
  q.push(root);
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

void BinarySearchTree::Hack() {
  if (root != nullptr) root->key_ = 10000;
}

void BinarySearchTree::dfs(struct BSTNode * curr) {
  if (curr == nullptr) return ;
  if (curr->left != nullptr) {
    dfs(curr->left);
  }
  cout<<curr->key_<<" ";
  if (curr->right != nullptr) {
    dfs(curr->right);
  }
}

void BinarySearchTree::fillMinMax(struct BSTNode * curr) {
  if (curr == nullptr) return ;
  int pending_min = curr->key_;
  int pending_max = curr->key_;
  if (curr->left != nullptr) {
    fillMinMax(curr->left);
    pending_min = min(pending_min, curr->left->min_);
  }
  if (curr->right != nullptr) {
    fillMinMax(curr->right);
    pending_max = max(pending_max, curr->right->max_);
  }
  curr->min_ = pending_min;
  curr->max_ = pending_max;
}
