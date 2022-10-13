class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = (int)nums.size(), max_len = nums[0];
        for (int i = 1; i < n; ++i) {
            if (i <= max_len) {
                max_len = std::max(max_len, i + nums[i]);
            } else {
                return false;
            }
        }
        return true;
    }
};
