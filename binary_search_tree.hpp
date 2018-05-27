#include <bits/stdc++.h>

using namespace std;

struct BSTNode {
  BSTNode(int key): key_(key) {
  }
  int key_;

  struct BSTNode * left_{nullptr};
  struct BSTNode * right_{nullptr};

  bool IsLeaf() {
    return left_ == nullptr && right_ == nullptr;
  }

  bool IsSingleLeft() {
    return left_ != nullptr && right_ == nullptr;
  }

  bool IsSingleRight() {
    return right_ != nullptr && left_ == nullptr;
  }
};


class BinarySearchTree {
  public:
    ~BinarySearchTree() {
        recursiveDestroy(root_);
    }
    void Insert(int key); // add new node by (key, associated_value).
    bool Has(int key) {
        struct BSTNode * curr = root_;
        while(curr != nullptr) {
            if (curr->key_ == key) return true;
            else if (key < curr->key_) {
                curr = curr->left_;
            } else {
                curr = curr->right_;
            }
        }
        return false;
    } 
    void Delete(int key); // delete node by key.
    size_t Size() {
        return size_;
    }
  private:
    void recursiveInsert(BSTNode * & curr, int key);
    void recursiveDelete(BSTNode * & curr, int key);
    void recursiveDestroy(BSTNode * & curr) {
        if (curr == nullptr) return ;
        if (curr->left_ != nullptr) {
            recursiveDestroy(curr->left_);
        }
        if (curr->right_ != nullptr) {
            recursiveDestroy(curr->right_);
        }

        delete curr;
        curr = nullptr;
    }
    struct BSTNode * root_{nullptr};
    size_t size_{0};
};

void BinarySearchTree::Insert(int key) {
    recursiveInsert(root_, key);
    size_++;
}

void BinarySearchTree::recursiveInsert(BSTNode * & curr, int key) {
    if (curr == nullptr) {
        curr = new BSTNode(key);
        return ;
    }

    if (key < curr->key_) {
        recursiveInsert(curr->left_, key);
    } else {
        recursiveInsert(curr->right_, key); 
    }
}

void BinarySearchTree::Delete(int key) {
    if (Has(key) == false) return ;
    recursiveDelete(root_, key);
    size_--;
} 

void BinarySearchTree::recursiveDelete(struct BSTNode * & curr, int key) {
    if (curr->key_ == key) {
        // find the target node to be deleted.
        if (curr->IsLeaf()) {
            delete curr;
            curr = nullptr;
        } else if (curr->IsSingleLeft()) {
            struct BSTNode * to_deleted = curr;
            curr = curr->left_;
            delete to_deleted;
        } else if (curr->IsSingleRight()) {
            struct BSTNode * to_deleted = curr;
            curr = curr->right_;
            delete to_deleted;
        } else { // two children.
            // find left max
            struct BSTNode * & left_max = curr->left_;
            while(left_max->right_ != nullptr) {
                left_max = left_max->right_;
            }

            swap(*curr, *left_max);
            recursiveDelete(left_max, left_max->key_);
        }
        return ;
    } else if (key < curr->key_) {
        recursiveDelete(curr->left_, key);
    } else {
        recursiveDelete(curr->right_, key);
    }
}
