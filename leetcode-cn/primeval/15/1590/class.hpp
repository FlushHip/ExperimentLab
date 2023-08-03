#include "headers.h"

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = static_cast<int>(nums.size());
        int k = std::accumulate(nums.begin(), nums.end(), 0,
            [p](int init, int item) { return (init + item) % p; });
        if (k == 0) {
            return 0;
        }
        std::unordered_map<int, int> ump;
        ump.emplace(0, -1);
        int min_len = n, sum = 0;
        for (int i = 0; i < n; ++i) {
            sum = (sum + nums[i]) % p;
            ump[sum] = i;
            if (auto it = ump.find((sum - k + p) % p); it != ump.end()) {
                min_len = std::min(min_len, i - it->second);
            }
        }
        return min_len == n ? -1 : min_len;
    }
};
