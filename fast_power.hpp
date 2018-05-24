#include <bits/stdc++.h>

using namespace std;
using INT = long long;

INT FastPow(INT x, INT n) {
    INT res = 1;
    INT base = x;
    while(n > 0) {
        if (n & 1) {
            res *= base;
        }
        base *= base;
        n >>= 1;
    }
    return res;
}

