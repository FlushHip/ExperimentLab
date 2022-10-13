class Solution {
    std::tuple<int, int, int, int> dfs(const std::vector<int> &nums, int lhs, int rhs) {
        if (lhs == rhs) {
            return { nums[lhs], nums[lhs], nums[lhs], nums[lhs] };
        }
        int mid = (lhs + rhs) / 2;
        auto [lhs_total_sum, lhs_l_sum, lhs_r_sum, lhs_max] = dfs(nums, lhs, mid);
        auto [rhs_total_sum, rhs_l_sum, rhs_r_sum, rhs_max] = dfs(nums, mid + 1, rhs);

        int total_sum = lhs_total_sum + rhs_total_sum;
        int l_sum = std::max(lhs_l_sum, lhs_total_sum + rhs_l_sum);
        int r_sum = std::max(rhs_r_sum, rhs_total_sum + lhs_r_sum);
        int max_sum = std::max({lhs_max, rhs_max, lhs_r_sum + rhs_l_sum});
        return { total_sum, l_sum, r_sum, max_sum };
    }
public:
    int maxSubArray(vector<int>& nums) {
        return std::get<3>(dfs(nums, 0, (int)(nums.size() - 1)));
    }
};
