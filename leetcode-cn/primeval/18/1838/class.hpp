#include "headers.h"

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());
        std::vector<long long> sums(n);
        // std::partial_sum(nums.begin(), nums.end(), std::back_inserter(sums));
        sums[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            sums[i] = sums[i - 1] + nums[i];
        }
        int lhs = 0, rhs = n;
        auto fn = [&](int len) -> bool {
            for (int i = len - 1; i < n; ++i) {
                if (sums[i] - (i - len < 0 ? 0 : sums[i - len]) + k >=
                    1LL * nums[i] * len) {
                    return true;
                }
            }
            return false;
        };
        while (lhs < rhs) {
            int mid = (lhs + rhs + 1) / 2;
            if (fn(mid)) {
                lhs = mid;
            } else {
                rhs = mid - 1;
            }
        }
        return rhs;
    }
};