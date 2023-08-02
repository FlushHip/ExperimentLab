#include "headers.h"

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        std::unordered_map<int, int> ust;
        int sum = 0, ans = 0;
        ust.emplace(0, 1);
        for (int i = 0; i < n; ++i) {
            sum = (sum + nums[i]) % k;
            if (sum < 0) {
                sum += k;
            }
            if (auto it = ust.find(sum); it != ust.end()) {
                ans += it->second;
            }
            ++ust[sum];
        }
        return ans;
    }
};
