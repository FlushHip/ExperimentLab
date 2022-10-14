class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = (int)nums.size();
        std::vector<int> prefix(n), suffix(n);
        std::partial_sum(nums.begin(), nums.end(), prefix.begin(), std::multiplies<>{});
        std::partial_sum(nums.rbegin(), nums.rend(), suffix.rbegin(), std::multiplies<>{});

        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = (i - 1 >= 0 ? prefix[i - 1] : 1)
                * (i + 1 < n ? suffix[i + 1] : 1);
        }
        return ans;
    }
};
