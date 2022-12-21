#include "headers.h"

class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        constexpr long long mod = 1e9 + 7;
        if (a > b) {
            std::swap(a, b);
        }
        int lm = std::lcm(a, b);

        long long lhs = 0, rhs = n;
        auto fn = [lm, a, b](auto x) { return x * (lm / a + lm / b - 1); };
        while (lhs < rhs) {
            auto mid = (lhs + rhs + 1) / 2;
            if (fn(mid) > n) {
                rhs = mid - 1;
            } else {
                lhs = mid;
            }
        }
        int res = n - fn(lhs);
        long long ans = lhs * lm % mod;
        long long offset = 0;
        for (int i = 1, j = 1; res; --res) {
            if (i * a < j * b) {
                offset = i++ * a;
            } else {
                offset = j++ * b;
            }
        }
        return (ans + offset) % mod;
    }
};
