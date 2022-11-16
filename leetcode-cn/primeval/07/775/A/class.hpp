#include "headers.h"

class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        long long part_num = 0;
        for (int i = 1; i < nums.size(); ++i) {
            part_num += nums[i - 1] > nums[i];
        }
        return part_num == global_num(nums);
    }

private:
    long long global_num(std::vector<int>& nums) {
        auto line(nums);
        return dfs(nums, 0, nums.size(), line);
    }

    long long dfs(std::vector<int>& nums,
        int lhs,
        int rhs,
        std::vector<int>& line) {
        if (rhs - lhs == 1) {
            return 0;
        }
        int mid = lhs + (rhs - lhs) / 2;
        long long ans = dfs(nums, lhs, mid, line) + dfs(nums, mid, rhs, line);
        int left = lhs, right = mid, index = 0;
        while (left < mid && right < rhs) {
            if (nums[left] < nums[right]) {
                line[index++] = nums[left++];
                ans += right - mid;
            } else {
                line[index++] = nums[right++];
            }
        }
        while (left < mid) {
            line[index++] = nums[left++];
            ans += right - mid;
        }
        while (right < rhs) {
            line[index++] = nums[right++];
        }
        std::copy(line.begin(), line.begin() + rhs - lhs, nums.begin() + lhs);
        return ans;
    }
};
