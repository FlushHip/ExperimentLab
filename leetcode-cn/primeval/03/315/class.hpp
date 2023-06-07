#include "headers.h"

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int offset = *std::min_element(nums.begin(), nums.end()) - 1;
        int top = *std::max_element(nums.begin(), nums.end()) - offset;
        std::vector<int> c(top + 1, 0);
        auto lowbit = [](int x) { return x & -x; };
        auto sum = [&](int x) {
            int ret = 0;
            for (; x > 0; x -= lowbit(x)) {
                ret += c[x];
            }
            return ret;
        };
        auto update = [&](int x) {
            for (; x <= top; x += lowbit(x)) {
                ++c[x];
            }
        };

        std::vector<int> ans(nums.size());
        for (int i = static_cast<int>(nums.size()) - 1; i >= 0; --i) {
            ans[i] = sum(nums[i] - offset - 1);
            update(nums[i] - offset);
        }
        return ans;
    }
};
