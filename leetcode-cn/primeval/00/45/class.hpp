class Solution {
public:
    int jump(vector<int>& nums) {
        int n = (int)nums.size(), max_len = 0, d = 0, ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            max_len = std::max(max_len, i + nums[i]);
            if (i == d) {
                ++ans;
                d = max_len;
            }
        }
        return ans;
    }
};
