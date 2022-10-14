class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        std::vector<int> ans;
        std::partial_sum(nums.begin(), nums.end()
            , std::back_inserter(ans));
        return ans;
    }
};
