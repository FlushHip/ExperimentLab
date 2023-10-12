#include "headers.h"

class Solution {
public:
    long long findTheArrayConcVal(vector<int>& nums) {
        auto ans = 0LL;
        int n = static_cast<int>(nums.size());
        int lhs = 0, rhs = n - 1;
        for (; lhs < rhs; ++lhs, --rhs) {
            auto sum = std::stoll(
                std::to_string(nums[lhs]).append(std::to_string(nums[rhs])));
            ans += sum;
        }
        if (lhs == rhs) {
            ans += nums[lhs];
        }
        return ans;
    }
};
