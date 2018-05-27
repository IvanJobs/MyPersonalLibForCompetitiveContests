#include <bits/stdc++.h>

using namespace std;

class RadixSort {
    public:
        static void Sort(std::vector<int> & a) {
            // get max position count.
            // Example: IntWidth(12345) == 5
            auto IntWidth = [](int v) {
                int res = 0;
                do {
                    res++;
                    v /= 10;
                } while(v > 0);
                return res;
            };

            // Example: GetShiftValue(12345, 2) == 4
            auto GetShiftValue = [](int v, int idx) {
                int res = v % 10;
                do {
                   idx--;
                   if (idx <= 0) break;
                   v /= 10;
                   res = v % 10;
                } while(true);

                return res;
            };

            int max_width = 0;
            for (auto & v: a) {
                max_width = max(max_width, IntWidth(v));
            }

            // becasue of 0..9
            int buckets[10];
            std::vector<int> b;
            b.resize(a.size());
            for (int i = 1; i <= max_width; i++) {
                memset(buckets, 0, sizeof(buckets));
                std::vector<int> digits_cache;
                for (size_t j = 0; j < a.size(); j++) {
                    int d = GetShiftValue(a[j], i);
                    cout<<d<<endl;
                    digits_cache.push_back(d);
                    buckets[d]++;
                } 

                // accum sum of buckets.
                for (int j = 1; j < 10; j++) buckets[j] += buckets[j - 1];

                for (size_t j = a.size() - 1; j >= 0; j--) {
                    int d = digits_cache[j];
                    b[buckets[d] - 1] = a[j];
                    buckets[d]--;
                }

                // swap a with b
                for (size_t j = 0; j < a.size(); j++) {
                    swap(a[j], b[j]);
                }
            }
        }
};
