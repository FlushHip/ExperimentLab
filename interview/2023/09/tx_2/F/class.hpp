#include <dbg.h>

class Solution {
public:
    int numsOfGoodMatrix(int n, int m, int x) {
        return mul(x, n) * mul(2 * mul(x / 2, n) % kmod, m - 1) % kmod;
    }

private:
    long long mul(long long x, long long y) {
        if (y == 0) {
            return 1;
        }
        auto half = mul(x, y / 2);
        return half * half % kmod * (y % 2 == 1 ? x : 1) % kmod;
    }

private:
    constexpr static long long kmod = 1e9 + 7;
};
