#include "headers.h"

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        for (int num : nums) {
            int index = (num - 1) % n;
            nums[index] += n;
        }
        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (nums[i] <= n) {
                ans.push_back(i + 1);
            }
        }
        return ans;
    }
};
