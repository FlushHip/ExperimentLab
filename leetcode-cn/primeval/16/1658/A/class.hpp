#include "headers.h"

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        std::vector<int> sums;
        std::partial_sum(nums.begin(), nums.end(), std::back_inserter(sums));
        if (sums.back() == x) {
            return nums.size();
        }
        int sum = 0, ans = std::numeric_limits<int>::max();
        for (int i = nums.size() - 1; i >= 0; --i) {
            if (sum == x) {
                ans = std::min(ans, static_cast<int>(nums.size()) - (i + 1));
                break;
            }
            auto it = std::lower_bound(sums.begin(), sums.end(), x - sum);
            if (it != sums.end() && *it == x - sum) {
                int index = it - sums.begin();
                if (index <= i) {
                    ans = std::min(ans,
                        index + 1 + (static_cast<int>(nums.size()) - (i + 1)));
                }
            }
            sum += nums[i];
        }
        return ans == std::numeric_limits<int>::max() ? -1 : ans;
    }
};
