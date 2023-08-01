#include "headers.h"

class Solution {
public:
    int sumOfPower(vector<int>& nums) {
        constexpr long long mod = 1e9 + 7;
        int n = static_cast<int>(nums.size());

        std::sort(nums.begin(), nums.end());

        long long f = nums[0];
        long long ans = 1LL * nums[0] * nums[0] % mod * f % mod;
        for (int i = 1; i < n; ++i) {
            ans = (ans + 1LL * nums[i] * nums[i] % mod * (f + nums[i]) % mod) %
                mod;
            f = (f * 2 % mod + nums[i]) % mod;
        }
        return ans;
    }
};
