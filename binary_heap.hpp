#include <bits/stdc++.h>

using namespace std;

class BinaryHeapMin {
  public:
    BinaryHeapMin();
    void Push(int key);
    void Pop();
    int Top();
    bool Empty();
  private:
    vector<int> a_;
};

BinaryHeapMin::BinaryHeapMin() {
  a_.clear();
  a_.push_back(0); // dummy element.
}

bool BinaryHeapMin::Empty() {
  return a_.size() <= 1;
}

void BinaryHeapMin::Push(int key) {
  a_.push_back(key);

  auto P = [](int idx) {
    return idx/2; 
  }; 

  int curr = a_.size() - 1; 
  while(curr > 1 && a_[P(curr)] > a_[curr]) {
    // exchange a_[P(curr)] with a_[curr]
    swap(a_[P(curr)], a_[curr]);
    curr = P(curr); 
  } 
}

void BinaryHeapMin::Pop() {
  // exchange a_[1] with a_[a_.size() - 1]
  if (a_.size() > 2) {
    swap(a_[1], a_[a_.size() - 1]);
  } 
  a_.pop_back(); // remove last element.

  int curr = 1;
  while(curr < a_.size()) {
    // find min
    int value_min = a_[curr];
    if (2 * curr < a_.size()) {
      value_min = min(value_min, a_[2 * curr]); 
    }
    if (2 * curr + 1 < a_.size()) {
      value_min = min(value_min, a_[2 * curr + 1]); 
    }

    if (value_min == a_[curr]) {
      break; // we are done.
    }
    if (2 * curr < a_.size() && value_min == a_[2 * curr]) {
      swap(a_[curr], a_[2 * curr]);
      curr = 2 * curr; 
    }
    if (2 * curr + 1 < a_.size() && value_min == a_[2 * curr + 1]) {
      swap(a_[curr], a_[2 * curr + 1]);
      curr = 2 * curr + 1; 
    }
  } 
}

int BinaryHeapMin::Top() {
  if (this->Empty()) return -1;
  // assume not empty()
  return a_[1];
}
