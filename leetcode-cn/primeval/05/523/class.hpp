#include "headers.h"

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        if (k == 1 && n > 1) {
            return true;
        }
        std::unordered_map<int, int> ust;
        int sum = 0;
        ust.emplace(0, -1);
        for (int i = 0; i < n; ++i) {
            sum = (sum + nums[i]) % k;
            if (auto it = ust.find(sum); it != ust.end()) {
                if (i - it->second > 1) {
                    return true;
                }
            } else {
                ust.emplace(sum, i);
            }
        }
        return false;
    }
};
