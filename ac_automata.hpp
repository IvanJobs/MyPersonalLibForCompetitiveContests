#include <bits/stdc++.h>

using namespace std;

using Index = int;
using Pattern = string;
using MatchResult = tuple<Index, Pattern>;
using MatchResults = vector<MatchResult>;

class ACAutoMeta {
    public:
        struct FakeNode {
            FakeNode() {
                for (size_t i = 0; i < 26; i++) children_[i] = nullptr;
            }
            struct FakeNode * fail_{nullptr};
            struct FakeNode * children_[26] {}; // suppose strings are in lowercase form.
            bool is_tail_{false}; 
            
            // edge leads to this node. which character this edge represents?
            // because string are all composed by lowercase letters, we can use Upper A as the default value.
            char c_{'A'};

            // when building fail links, we need to seek to nodes' parents.
            struct FakeNode * parent_{nullptr};
        };

        using Node = struct FakeNode;

    public:
        ACAutoMeta() = default;
        ~ACAutoMeta() {
            recursiveDestroyTrie(root_);        
        }

        void AddPatternStr(string pattern) {
            patterns_.push_back(pattern);
        }

        void Build() {
            if (patterns_.empty()) return ;

            // first we need to build a trie based on patterns_.
            {
                if (root_ == nullptr) root_ = new Node();

                for (auto & p: patterns_) {
                    Node * curr = root_;
                    Node * parent = nullptr;
                    char c = 'A';
                    for (size_t i = 0; i < p.size(); i++) {

                        curr->parent_ = parent; // set parent_.
                        curr->c_ = c; // set edge character.

                        int target_index = p[i] - 'a';
                       
                        // mark tail.
                        if (i == p.size() - 1) {
                            curr->is_tail_ = true;
                        }

                        parent = curr;
                        c = p[i];

                        if (curr->children_[target_index] == nullptr) {
                            curr->children_[target_index] = new Node();
                        }
                        curr = curr->children_[target_index];
                    }
                } 
            }

            // then we build fail links.
            {
                // first, build root and root's sons.
                //
                root_->fail_ = root_; 
                for (size_t i = 0; i < 26; i++) {
                    if (root_->children_[i] != nullptr) {
                        root_->children_[i]->fail_ = root_;
                    }
                }
                // then, bfs.
                //
                queue<Node *> q;
                q.push(root_);
                while(q.empty() == false) {
                    Node * curr = q.front();
                    q.pop();

                    if (curr == nullptr) continue;
        
                    // collect nodes from the next level.
                    for (size_t i = 0; i < 26; i++) q.push(curr->children_[i]); 

                    if (curr->fail_ != nullptr) {
                        continue;
                    } 

                    // starting to seek fail_.
                    //
                    // 0. find parent's fail_, 
                    // 1. if parent's fail_ is root_, then curr's fail_ is root.
                    // 2. else  then check if curr's char is in parent's fail_'s char?
                    //      if it is:   curr's fail_ is set to parent's fail_'s char's pointer.
                    //      else it is not: treat   
                    if (curr->parent_ == nullptr) continue;
                    Node * fail_node = curr->parent_->fail_; 
                    char target_index = curr->c_ - 'a';
                    while(true) {
                        if (fail_node->children_[target_index] != nullptr) {
                            curr->fail_ = fail_node->children_[target_index];
                            break;
                        } else {
                            if (fail_node == root_) break;
                            fail_node = fail_node->fail_;
                        }  
                    }
                }
            }
        }
        
        MatchResults Match(string text) {
            return MatchResults();
        }

        bool IsMatch(string text) {
            if (root_ == nullptr) return false;

            Node * curr = root_;
            size_t i = 0;
            while(i < text.size()) {
                // cout<<"i:"<<i<<",curr->c_:"<<curr->c_<<endl;
                int target_index = text[i] - 'a';
                if (curr->children_[target_index] == nullptr) {
                    if (curr == root_) {
                        i++;
                    }
                    curr = curr->fail_;  
                } else {
                    if (curr->children_[target_index]->is_tail_) {
                        return true;
                    }
                    i++;
                    curr = curr->children_[target_index];
                }
            }
            return false;
        }
    private:
        vector<string> patterns_{};
        Node * root_{nullptr};
    private:
        void recursiveDestroyTrie(Node * curr) {
            // cout<<"curr->c_:"<<curr->c_<<endl;
            if (curr == nullptr) return ;
            for (size_t i = 0; i < 26; i++) {
                // cout<<i<<endl;
                recursiveDestroyTrie(curr->children_[i]);
            }
            delete curr;
            curr = nullptr;

            return ;
        }
};
