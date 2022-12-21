#include "headers.h"

class Solution {
public:
    int sumSubseqWidths(vector<int>& nums) {
        constexpr long long mod = 1e9 + 7;
        auto power_2 = [mod](int n) {
            long long ret = 1;
            for (long long base = 2ll; n; n >>= 1) {
                if (n & 1) {
                    ret = ret * base % mod;
                }
                base = (base * base) % mod;
            }
            return ret;
        };
        std::sort(nums.begin(), nums.end());
        long long ans = 0;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            ans =
                (ans + nums[i] * (mod + power_2(i) - power_2(n - i - 1))) % mod;
        }
        return ans;
    }
};
