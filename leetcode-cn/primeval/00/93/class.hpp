#include "headers.h"

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        int n = static_cast<int>(s.size());
        if (n < 4 || n > 12) {
            return {};
        }
        std::vector<std::string> ans;
        std::vector<std::string_view> nums;
        dfs(s, 0, nums, ans);
        return ans;
    }

private:
    void dfs(std::string_view s,
        unsigned int index,
        std::vector<string_view>& nums,
        std::vector<std::string>& ans) {
        if (index == s.size()) {
            if (nums.size() == 4) {
                std::stringstream ss;
                ss << nums[0] << '.' << nums[1] << '.' << nums[2] << '.'
                   << nums[3];
                ans.emplace_back(ss.str());
            }
            return;
        }
        if (nums.size() == 4 || s.size() - index < 4 - nums.size() ||
            s.size() - index > 4 * (4 - nums.size())) {
            return;
        }
        for (int len = 1; len <= 3 && index + len <= s.size(); ++len) {
            int value = 0;
            std::from_chars(s.data() + index, s.data() + index + len, value);
            if (len == 1 && value == 0) {
                nums.emplace_back(s.data() + index, 1);
                dfs(s, index + 1, nums, ans);
                nums.pop_back();
                break;
            }
            if (value > 0 && value <= 0xff) {
                nums.emplace_back(s.data() + index, len);
                dfs(s, index + len, nums, ans);
                nums.pop_back();
            }
        }
    }
};
