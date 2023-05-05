#include "headers.h"

class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        return std::max(
            aux(nums, firstLen, secondLen), aux(nums, secondLen, firstLen));
    }

private:
    int aux(const std::vector<int>& nums, int a, int b) {
        int lhs = std::accumulate(nums.begin(), nums.begin() + a, 0),
            rhs = std::accumulate(nums.begin() + a, nums.begin() + a + b, 0);
        int ret_l = lhs, ans = ret_l + rhs;
        int n = static_cast<int>(nums.size());
        for (int i = a + 1; i + b <= n; ++i) {
            lhs = lhs + nums[i - 1] - nums[i - a - 1];
            ret_l = std::max(ret_l, lhs);
            rhs = rhs + nums[i + b - 1] - nums[i - 1];
            ans = std::max(ans, ret_l + rhs);
        }
        return ans;
    }
};
