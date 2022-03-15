class Solution {
    enum { MAX_BIT = 16 };
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int n = (int)nums.size();
        std::map<int, int> ans;
        for (int i = 1; i < (1 << n); ++i) {
            std::bitset<MAX_BIT> bits(i);
            int s = 0;
            for (int j = 0; j < n; ++j) {
                s |= bits[j] ? nums[j] : 0;
            }
            ++ans[s];
        }

        return ans.rbegin()->second;
    }
};
