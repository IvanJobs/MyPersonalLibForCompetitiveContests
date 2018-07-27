#include <bits/stdc++.h>

using namespace std;
int ex_gcd(int a, int b, int & x, int & y) {
    struct FakeItem {
        int r;
        int s;
        int t;
    };
    using Item = struct FakeItem;

    Item S[2];
    S[0] = {a, 1, 0};
    S[1] = {b, 0, 1};
    
    while(true) {
        if (S[1].r == 0) break;

        // transform.
        {
            Item tmp;
            int q = S[0].r / S[1].r;
            tmp.r = S[0].r - q * S[1].r;
            tmp.s = S[0].s - q * S[1].s;
            tmp.t = S[0].t - q * S[1].t;

            swap(S[0], S[1]);
            swap(S[1], tmp);
        }
    }

    x = S[0].s;
    y = S[0].t;

    return S[0].r;
}
