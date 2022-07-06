class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int n = (int)nums.size(), d = 1e5, ans = 0;
        for (int i = 0; i < n - 2; ++i) {
            for (int lhs = i + 1, rhs = n - 1; lhs < rhs;) {
                if (std::abs(nums[i] + nums[lhs] + nums[rhs] - target) < d) {
                    ans = nums[i] + nums[lhs] + nums[rhs];
                    d = std::abs(ans - target);
                }
                if (nums[i] + nums[lhs] + nums[rhs] > target) {
                    --rhs;
                } else if (nums[i] + nums[lhs] + nums[rhs] < target) {
                    ++lhs;
                } else {
                    return target;
                }
            }
        }
        return ans;
    }
};
