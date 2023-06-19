#include "headers.h"

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int ans = 0;
        std::bitset<32> bit_a(a), bit_b(b), bit_c(c);
        for (int i = 0; i < 32; ++i) {
            if ((bit_a[i] | bit_b[i]) != bit_c[i]) {
                if (bit_c[i] == 1) {
                    ++ans;
                } else {
                    if (bit_a[i] == 1 && bit_b[i] == 1) {
                        ans += 2;
                    } else {
                        ++ans;
                    }
                }
            }
        }
        return ans;
    }
};
