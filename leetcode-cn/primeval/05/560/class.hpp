// TAG : 连续字串和等于目标值
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        std::map<int, int> mp{ { 0, 1 } };
        int pre = 0, ans = 0;
        for (const auto num : nums) {
            pre += num;
            if (mp.count(pre - k)) {
                ans += mp[pre - k];
            }
            ++mp[pre];
        }
        return ans;
    }
};
