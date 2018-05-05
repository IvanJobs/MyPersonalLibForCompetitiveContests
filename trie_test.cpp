#include <bits/stdc++.h>
#include "trie.hpp"

using namespace std;

int main() {
    Trie t;

    vector<string> v{"hello", "world"};
    for (auto s: v) t.Insert(s);

    if (t.Has("hello")) cout<<"Pass case 1"<<endl;
    else cout<<"Fail case 1"<<endl;

    if (t.Has("he")) cout<<"Fail case 2"<<endl;
    else cout<<"Pass case 2"<<endl;
    return 0;
}
