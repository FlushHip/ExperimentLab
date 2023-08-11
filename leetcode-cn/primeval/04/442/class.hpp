#include "headers.h"

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        for (int i = 0; i < n; ++i) {
            int real = (nums[i] - 1) % n;
            nums[real] += n;
        }
        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (2 == (nums[i] - 1) / n) {
                ans.emplace_back(i + 1);
            }
        }
        return ans;
    }
};
