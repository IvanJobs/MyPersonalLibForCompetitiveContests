#include <bits/stdc++.h>
#include "binary_heap.hpp"
using namespace std;

int main() {
  BinaryHeapMin bh;
  for (int i = 1; i < 10; i++) {
    bh.Push(i);
  }

  if (bh.Top() == 1) {
    cout<<"Pass case 1"<<endl;
  } else {
    cout<<"Fail case 1"<<endl;
  }

  bh.Pop();
  if (bh.Top() == 2) {
    cout<<"Pass case 2"<<endl; 
  } else {
    cout<<"Fail case 2"<<endl;
  }

  bh.Push(1);
  if (bh.Top() == 1) {
    cout<<"Pass case 3"<<endl;
  } else {
    cout<<"Fail case 3"<<endl;
  }
  return 0;
}
