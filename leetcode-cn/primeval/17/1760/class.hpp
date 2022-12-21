#include "headers.h"

class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        std::sort(nums.begin(), nums.end(), std::greater<int>{});
        int lhs = 1, rhs = nums.front();
        auto fn = [&](int x) {
            int sum = 0;
            for (auto num : nums) {
                if (num <= x) {
                    break;
                }
                sum += (num + x - 1) / x - 1;
            }
            return sum <= maxOperations;
        };
        while (lhs < rhs) {
            int mid = (lhs + rhs) / 2;
            if (!fn(mid)) {
                lhs = mid + 1;
            } else {
                rhs = mid;
            }
        }
        return lhs;
    }
};
