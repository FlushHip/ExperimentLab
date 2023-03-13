#include "headers.h"

class Solution {
public:
    vector<vector<int>> combine(int nn, int kk) {
        std::vector<int> nums(nn, 0);
        int n = nums.size();
        for (auto it = nums.rbegin(); kk-- && it != nums.rend(); ++it) {
            *it = 1;
        }
        std::vector<std::vector<int>> ans;
        while (true) {
            {
                int digit = 1;
                std::vector<int> line;
                for (auto it = nums.rbegin(); it != nums.rend();
                     ++it, ++digit) {
                    if (*it == 1) {
                        line.push_back(digit);
                    }
                }
                ans.push_back(std::move(line));
            }
            int index = n - 1;
            while (index - 1 >= 0 && nums[index - 1] >= nums[index]) {
                --index;
            }
            if (index == 0) {
                break;
            }
            int pos = n - 1;
            while (nums[pos] <= nums[index - 1]) {
                --pos;
            }
            std::swap(nums[index - 1], nums[pos]);
            std::reverse(nums.begin() + index, nums.end());
        }
        return ans;
    }
};
