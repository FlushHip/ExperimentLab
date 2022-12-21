#include "headers.h"

class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> dp_max(n), dp_min(n);
        dp_max[0] = nums[0];
        dp_min[n - 1] = nums[n - 1];
        for (int i = 1; i < n; ++i) {
            dp_max[i] = std::max(nums[i], dp_max[i - 1]);
            dp_min[n - i - 1] = std::min(nums[n - i - 1], dp_min[n - i]);
        }
        for (int i = 0; i < n - 1; ++i) {
            if (dp_max[i] <= dp_min[i + 1]) {
                return i + 1;
            }
        }
        return 0;
    }
};
