#ifndef INTERVAL_TREE_HPP_
#define INTERVAL_TREE_HPP_
#include <bits/stdc++.h>
using namespace std;

struct DummyNode {
    DummyNode(int key, int right):key_(key), right_(right), max_(right) {
        srand(time(nullptr));
        fix_ = rand();
    }
    int key_; // actually, it's the left_.
    int right_;
    int max_;
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

using Node = struct DummyNode;

class IntervalTree {
    public:
        IntervalTree() = default;
        ~IntervalTree();
        void Insert(int key, int right) {
            recursiveInsert(root_, key, right);
            size++;
        }
        void Delete(int key, int right) {
            if (this->Has(key, right) == false) return ;
            recursiveDelete(root_, key, right);
            size--;
        }
        bool Has(int key, int right);
        size_t Size() {
            return size;
        }
    private:
        void recursiveInsert(Node * & curr, int key, int right);
        void recursiveDelete(Node * & curr, int key, int right);
        void nodeSwap(Node * lhs, Node * rhs) {
            swap(lhs->key_, rhs->key_);
            swap(lhs->right_, rhs->right_);
            swap(lhs->max_, rhs->max_);
            swap(lhs->fix_, rhs->fix_);
        }

        Node * & findRightSubtreeMin(Node * & curr);
        Node * & findLeftSubtreeMax(Node * & curr);

        void rightRotate(Node * & parent);
        void leftRotate(Node * & parent);
    private:
        Node * root_{nullptr};
        size_t size{0};
};

IntervalTree::~IntervalTree() {
    if (root_ == nullptr) return ;
    // gather all pointers
    vector<Node *> v;
    queue<Node*> q;
    q.push(root_);
    while(q.empty() == false) {
        Node * curr = q.front();
        v.push_back(curr);
        if (curr->left_ != nullptr) q.push(curr->left_);
        if (curr->right_ != nullptr) q.push(curr->right_);
        q.pop();
    }
    for (Node * p: v) delete p;
}

void IntervalTree::recursiveInsert(Node * & curr, int key, int right) {
    if (curr == nullptr) {
        // find where to insert the curr node.
        curr = new Node(key);
        
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

void IntervalTree::recursiveDelete(Node * & curr, int key, int right) {
    if (curr == nullptr) return ;
    if (key < curr->key_) {
        recursiveDelete(curr->left_, key);
    } else if (key > curr->key_) {
        recursiveDelete(curr->right_, key);
    } else {
        // found the node to be deleted.
        if (curr->Leaf()) {
            Node * tobe_deleted = curr;
            curr = nullptr;
            delete tobe_deleted;
        } else if (curr->SingleLeft()) {
            Node * tobe_deleted = curr;
            curr = curr->left_;
            delete tobe_deleted;
        } else if (curr->SingleRight()) {
            Node * tobe_deleted = curr;
            curr = curr->right_;
            delete tobe_deleted;
        } else { // two children
            Node * & right_min = findRightSubtreeMin(curr->right_);
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

bool IntervalTree::Has(int key, int right) {
    Node * curr = root_;
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

Node * & IntervalTree::findRightSubtreeMin(Node * & curr) {
    while(curr->left_ != nullptr) {
        curr = curr->left_;
    }
    return curr; 
}

Node * & IntervalTree::findLeftSubtreeMax(Node * & curr) {
    while(curr->right_ != nullptr) {
        curr = curr->right_;
    }
    return curr;
}

void IntervalTree::leftRotate(Node * & x) {
    Node * & y = x->right_;
    Node * & a = x->left_;
    Node * & b = y->left_;
    Node * & c = y->right_;

    x->right_ = b;
    y->left_ = x;
    x = y;
}

void IntervalTree::rightRotate(Node * & y) {
    Node * & x = y->left_;
    Node * & a = x->left_;
    Node * & b = x->right_;
    Node * & c = y->right_;
    
    y->left_ = b;
    x->right_ = y;
    y = x;
}

#endif
