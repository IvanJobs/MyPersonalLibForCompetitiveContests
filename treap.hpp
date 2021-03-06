#ifndef TREAP_HPP_
#define TREAP_HPP_
#include <bits/stdc++.h>
using namespace std;

struct DummyNode {
    DummyNode(int key):key_(key) {
        srand(time(nullptr));
        fix_ = rand();
    }
    int key_;
    int fix_;
    struct DummyNode * left_{nullptr};
    struct DummyNode * right_{nullptr};

    bool Leaf() {
        return (left_ == nullptr && right_ == nullptr);
    }

    bool SingleLeft() {
        return (left_ != nullptr && right_ == nullptr);
    } 

    bool SingleRight() {
        return (left_ == nullptr && right_ != nullptr); 
    }

    bool TwoChildren() {
        return (left_ != nullptr && right_ != nullptr);
    }
};

using TreapNode = struct DummyNode;

class Treap {
    public:
        Treap() = default;
        ~Treap();
        void Insert(int key) {
            recursiveInsert(root_, key);
            size++;
        }
        void Delete(int key) {
            if (this->Has(key) == false) return ;
            recursiveDelete(root_, key);
            size--;
        }
        bool Has(int key);
        size_t Size() {
            return size;
        }
    private:
        void recursiveInsert(TreapNode * & curr, int key);
        void recursiveDelete(TreapNode * & curr, int key);
        void nodeSwap(TreapNode * lhs, TreapNode * rhs) {
            swap(lhs->key_, rhs->key_);
            swap(lhs->fix_, rhs->fix_);
        }

        TreapNode * & findRightSubtreeMin(TreapNode * & curr);
        TreapNode * & findLeftSubtreeMax(TreapNode * & curr);

        void rightRotate(TreapNode * & parent);
        void leftRotate(TreapNode * & parent);
    private:
        TreapNode * root_{nullptr};
        size_t size{0};
};

Treap::~Treap() {
    if (root_ == nullptr) return ;
    // gather all pointers
    vector<TreapNode *> v;
    queue<TreapNode*> q;
    q.push(root_);
    while(q.empty() == false) {
        TreapNode * curr = q.front();
        v.push_back(curr);
        if (curr->left_ != nullptr) q.push(curr->left_);
        if (curr->right_ != nullptr) q.push(curr->right_);
        q.pop();
    }
    for (TreapNode * p: v) delete p;
}

void Treap::recursiveInsert(TreapNode * & curr, int key) {
    if (curr == nullptr) {
        // find where to insert the curr node.
        curr = new TreapNode(key);
        
        return ;
    }
    if (key <= curr->key_) {
        recursiveInsert(curr->left_, key); 
        if (curr->left_->fix_ < curr->fix_) {
            rightRotate(curr); 
        }
    } else {
        recursiveInsert(curr->right_, key);
        if (curr->right_->fix_ < curr->fix_) {
            leftRotate(curr);
        }
    }
}

void Treap::recursiveDelete(TreapNode * & curr, int key) {
    if (curr == nullptr) return ;
    if (key < curr->key_) {
        recursiveDelete(curr->left_, key);
    } else if (key > curr->key_) {
        recursiveDelete(curr->right_, key);
    } else {
        // found the node to be deleted.
        if (curr->Leaf()) {
            TreapNode * tobe_deleted = curr;
            curr = nullptr;
            delete tobe_deleted;
        } else if (curr->SingleLeft()) {
            TreapNode * tobe_deleted = curr;
            curr = curr->left_;
            delete tobe_deleted;
        } else if (curr->SingleRight()) {
            TreapNode * tobe_deleted = curr;
            curr = curr->right_;
            delete tobe_deleted;
        } else { // two children
            TreapNode * & right_min = findRightSubtreeMin(curr->right_);
            this->nodeSwap(right_min, curr);
            
            recursiveDelete(right_min, key);
            
            // maintain curr, it is possible that curr->fix_ brokes heap properties.
            while(true) {
                if (curr->Leaf()) break;
                else if (curr->SingleLeft()) {
                    if (curr->fix_ <= curr->left_->fix_) break;
                    else {
                        rightRotate(curr);
                        curr = curr->right_;
                    }
                } else if (curr->SingleRight()) {
                    if (curr->fix_ <= curr->right_->fix_) break;
                    else {
                        leftRotate(curr);
                        curr = curr->left_;
                    }
                } else {
                    int min_fix = min(curr->fix_, curr->left_->fix_); 
                    min_fix = min(min_fix, curr->right_->fix_); 
                    if (min_fix == curr->fix_) break;
                    else if (min_fix == curr->left_->fix_) {
                        rightRotate(curr);
                        curr = curr->right_;
                    } else {
                        leftRotate(curr);
                        curr = curr->left_;
                    }
                }
            }
        }
    }
}

bool Treap::Has(int key) {
    TreapNode * curr = root_;
    while(curr != nullptr) {
        if (key < curr->key_) {
            curr = curr->left_;
        } else if (key > curr->key_) {
            curr = curr->right_;
        } else {
            return true;
        }
    }
    return false;
}

TreapNode * & Treap::findRightSubtreeMin(TreapNode * & curr) {
    while(curr->left_ != nullptr) {
        curr = curr->left_;
    }
    return curr; 
}

TreapNode * & Treap::findLeftSubtreeMax(TreapNode * & curr) {
    while(curr->right_ != nullptr) {
        curr = curr->right_;
    }
    return curr;
}

void Treap::leftRotate(TreapNode * & x) {
    TreapNode * & y = x->right_;
    TreapNode * & a = x->left_;
    TreapNode * & b = y->left_;
    TreapNode * & c = y->right_;

    x->right_ = b;
    y->left_ = x;
    x = y;
}

void Treap::rightRotate(TreapNode * & y) {
    TreapNode * & x = y->left_;
    TreapNode * & a = x->left_;
    TreapNode * & b = x->right_;
    TreapNode * & c = y->right_;
    
    y->left_ = b;
    x->right_ = y;
    y = x;
}

#endif
