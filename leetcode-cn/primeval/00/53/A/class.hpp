class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_sum = nums[0];
        int sum = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i) {
            sum = max(nums[i], sum + nums[i]);
            max_sum = max(max_sum, sum);
        }
        return max_sum;
    }
};
