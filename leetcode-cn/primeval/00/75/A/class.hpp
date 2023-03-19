#include "headers.h"

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        auto fn = [&nums, n](int l_t, int r_t) {
            int lhs = 0, rhs = n - 1;
            while (lhs < rhs) {
                for (; lhs < rhs && nums[lhs] != r_t; ++lhs) {
                }
                for (; lhs < rhs && nums[rhs] != l_t; --rhs) {
                }
                if (lhs < rhs) {
                    std::swap(nums[lhs], nums[rhs]);
                }
            }
        };
        fn(0, 1);
        fn(0, 2);
        fn(1, 2);
    }
};
