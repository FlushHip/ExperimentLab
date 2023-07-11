#include "headers.h"

class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        std::unordered_map<int, int> ump;
        for (auto num : nums) {
            if (++ump[num] > k) {
                return -1;
            }
        }

        int n = static_cast<int>(nums.size());
        std::vector<std::vector<int>> dp(1 << n, std::vector<int>(n, -1));
        std::sort(nums.begin(), nums.end());
        return dfs((1 << n) - 1, 0, n / k, dp, nums);
    }

private:
    static int lowbit(int x) { return x & -x; }

    static int bit_cnt(int x) {
        int ret = 0;
        for (; x; x -= lowbit(x)) {
            ++ret;
        }
        return ret;
    }

    static int bit_index(int lb) {
        int ret = 0;
        for (; lb; lb >>= 1) {
            ++ret;
        }
        return ret - 1;
    }

    int dfs(int rest,
        int pre,
        const int size,
        std::vector<std::vector<int>>& dp,
        const std::vector<int>& nums) const {
        if (rest == 0) {
            return 0;
        }
        if (bit_cnt(rest) % size == 0) {
            int lb = lowbit(rest);
            if (dp[rest][0] != -1) {
                return dp[rest][0];
            }
            return dp[rest][0] = dfs(rest ^ lb, bit_index(lb), size, dp, nums);
        }
        if (dp[rest][pre] != -1) {
            return dp[rest][pre];
        }
        int last = nums[pre], n = static_cast<int>(nums.size());
        int ret = std::numeric_limits<int>::max();
        for (int i = pre + 1; i < n; ++i) {
            if (rest >> i & 1 && last != nums[i]) {
                last = nums[i];
                int res = dfs(rest ^ 1 << i, i, size, dp, nums);
                if (res != std::numeric_limits<int>::max()) {
                    ret = std::min(ret, nums[i] - nums[pre] + res);
                }
            }
        }
        return dp[rest][pre] = ret;
    }
};
