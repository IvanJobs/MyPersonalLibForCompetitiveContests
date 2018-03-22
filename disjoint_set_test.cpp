#include <bits/stdc++.h>
#include "disjoint_set.hpp"
using namespace std;

int main() {
  DisjointSet ds;
  for (auto i = 0; i < 10; i++) {
    ds.AddSet(std::to_string(i));
  }

  if (ds.Root("0") != ds.Root("1")) {
    cout<<"Pass 1"<<endl;
  } else cout<<"Fail 1"<<endl;

  ds.Union("5", "6");
  if (ds.Root("5") == ds.Root("6")) {
    cout<<"Pass 2"<<endl;
  } else cout<<"Fail 2"<<endl;

  ds.Union("5", "7");
  if (ds.Root("6") == ds.Root("7")) cout<<"Pass 3"<<endl;
  else cout<<"Fail 3"<<endl;
  return 0;
}
