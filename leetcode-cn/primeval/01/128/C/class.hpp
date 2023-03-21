#include "headers.h"

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        std::unordered_map<int, int> pre;
        for (int num : nums) {
            pre[num] = num;
        }
        std::function<std::optional<int>(int)> find =
            [&](int x) -> std::optional<int> {
            if (pre.find(x) == pre.end()) {
                return {};
            }
            return pre[x] == x ? x : pre[x] = find(pre[x]).value();
        };
        for (int num : nums) {
            if (auto it = find(num + 1); it.has_value()) {
                int x = find(num).value();
                int y = it.value();
                pre[x] = y;
            }
        }
        int ans = 0;
        for (int num : nums) {
            int right = find(num).value();
            ans = std::max(ans, right - num + 1);
        }
        return ans;
    }
};
