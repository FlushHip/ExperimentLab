#include "headers.h"

class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        constexpr long long mod = 1e9 + 7;
        if (a > b) {
            std::swap(a, b);
        }
        int lm = std::lcm(a, b);

        long long lhs = a - 1, rhs = static_cast<long long>(n) * a;
        auto fn = [lm, a, b](auto x) { return x / a + x / b - x / lm; };
        while (lhs < rhs) {
            auto mid = (lhs + rhs + 1) / 2;
            if (fn(mid) >= n) {
                rhs = mid - 1;
            } else {
                lhs = mid;
            }
        }
        return (lhs + 1) % mod;
    }
};
