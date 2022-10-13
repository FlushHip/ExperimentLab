#include <algorithm>
#include "headers.h"

class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if ((sum % k) != 0) {
            return false;
        }
        if (k == 1) {
            return true;
        }
        int b = sum / k;
        std::sort(nums.begin(), nums.end());
        for (int rhs = (int)(nums.size()) - 1; rhs >= 0 && nums[rhs] >= b;
             --rhs) {
            if (nums[rhs] > b) {
                return false;
            }
            nums.pop_back();
            --k;
        }
        if (!k) {
            return true;
        }
        if (nums.front() + nums.back() > b) {
            return false;
        }
        std::reverse(nums.begin(), nums.end());
        std::vector<int> accs(k, 0);
        return dfs(0U, accs, nums, b);
    }

private:
    bool dfs(unsigned index,
        std::vector<int>& accs,
        const std::vector<int>& nums,
        int b) {
        if (index == nums.size()) {
            return std::all_of(
                accs.begin(), accs.end(), [b](int acc) { return acc == b; });
        }
        for (auto& acc : accs) {
            if (acc + nums[index] <= b) {
                acc += nums[index];
                if (dfs(index + 1, accs, nums, b)) {
                    return true;
                }
                acc -= nums[index];
            }
        }
        return false;
    }
};
