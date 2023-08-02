#include "headers.h"

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        std::unordered_map<int, int> ump;
        ump.emplace(0, -1);
        int sum = 0, max_len = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i] == 0 ? 1 : -1;
            if (auto it = ump.find(sum); it != ump.end()) {
                max_len = std::max(max_len, i - it->second);
            } else {
                ump.emplace(sum, i);
            }
        }
        return max_len;
    }
};
