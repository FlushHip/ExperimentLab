#include "headers.h"

class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::vector<std::unordered_map<int, int>> dp(n);
        int ans = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                int d = nums[i] - nums[j];
                int max_value =
                    1 + (dp[j].find(d) != dp[j].end() ? dp[j][d] : 1);
                if (auto it = dp[i].find(d); it == dp[i].end()) {
                    dp[i].emplace(d, max_value);
                } else {
                    it->second = std::max(it->second, max_value);
                }
            }
            ans = std::max(ans,
                std::max_element(dp[i].begin(), dp[i].end(),
                    [](const auto& lhs, const auto& rhs) {
                        return lhs.second < rhs.second;
                    })
                    ->second);
        }
        return ans;
    }
};
