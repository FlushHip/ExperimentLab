#include <algorithm>
#include <initializer_list>

#include <dbg.h>

class Solution {
public:
    int getSubarrayNum(std::vector<int>& a, int x) {
        constexpr long long mod = 1e9 + 7;
        int n = static_cast<int>(a.size());
        std::vector<long long> num_2(n, 0), num_5(n, 0);
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int num = a[i]; num % 2 == 0; num /= 2) {
                ++sum;
            }
            num_2[i] = sum;

            sum = 0;
            for (int num = a[i]; num % 5 == 0; num /= 5) {
                ++sum;
            }
            num_5[i] = sum;
        }
        dbg(a, num_2, num_5);
        auto ans = 0LL;
        auto sum_2 = 0LL, sum_5 = 0LL;
        for (int rhs = 0, lhs = 0; rhs < n; ++rhs) {
            sum_2 += num_2[rhs];
            sum_5 += num_5[rhs];
            while (std::min(sum_2, sum_5) >= x) {
                dbg((std::initializer_list<int>{lhs, rhs}));
                sum_2 -= num_2[lhs];
                sum_5 -= num_5[lhs];
                ++lhs;
            }
            ans = (ans + lhs) % mod;
        }
        return ans;
    }
};
