#include <bits/stdc++.h>

using namespace std;

using Index = int;
using Pattern = string;
using MatchResult = tuple<Index, Pattern>;
using MatchResults = vector<MatchResult>;

class ACAutoMeta {
    public:
        struct FakeNode {
            struct FakeNode * fail_{nullptr};
            struct FakeNode * children_[26] {nullptr}; // suppose strings are in lowercase form.
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
        
        }

        void AddPatternStr(string pattern) {
            patterns_.push_back(pattern);
        }

        void Build() {
            if (patterns_.empty()) return ;

            // first we need to build a trie based on patterns_.
            {
                for (auto & p: patterns_) {
                    Node * curr = root_;
                    Node * parent = nullptr;
                    char c = 'A';
                    for (size_t i = 0; i < p.size(); i++) {
                        if (curr == nullptr) {
                            curr = new Node();
                        }

                        curr->parent_ = parent; // set parent_.
                        curr->c_ = c; // set edge character.

                        int target_index = p[i] - 'a';
                       
                        // mark tail.
                        if (i == p.size() - 1) {
                            curr->is_tail_ = true;
                        }

                        parent = curr;
                        c = p[i];

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
                    Node * fail_node = curr->parent_->fail_; // curr->parent_ cannot be nullptr.
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
            return true;
        }
    private:
        vector<string> patterns_{};
        Node * root_{nullptr};
};
