#include <algorithm>

#include <dbg.h>

class Solution {
public:
    int getSubarrayNum(std::vector<int>& a, int x) {
        constexpr long long mod = 1e9 + 7;
        int n = static_cast<int>(a.size());
        std::vector<long long> pre_2(n + 1, 0), pre_5(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int sum = 0;
            for (int num = a[i]; num % 2 == 0; num /= 2) {
                ++sum;
            }
            pre_2[i + 1] = pre_2[i] + sum;

            sum = 0;
            for (int num = a[i]; num % 5 == 0; num /= 5) {
                ++sum;
            }
            pre_5[i + 1] = pre_5[i] + sum;
        }
        dbg(pre_2, pre_5);
        auto ans = 0LL;
        for (int i = 1; i <= n; ++i) {
            int t_2 = pre_2[i] - x;
            int t_5 = pre_5[i] - x;
            if (t_2 < 0 || t_5 < 0) {
                continue;
            }
            long long idx_2 = std::upper_bound(pre_2.begin() + 1,
                                  pre_2.begin() + 1 + i, t_2) -
                pre_2.begin() - 1;
            long long idx_5 = std::upper_bound(pre_5.begin() + 1,
                                  pre_5.begin() + 1 + i, t_5) -
                pre_5.begin() - 1;
            auto idx = std::min(idx_2, idx_5);
            dbg(i, idx);
            ans = (ans + idx + 1) % mod;
        }
        return ans;
    }
};
