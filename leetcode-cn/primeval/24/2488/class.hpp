#include "headers.h"

class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        for (int& num : nums) {
            num = num == k ? 0 : num > k ? 1 : -1;
        }
        std::unordered_map<int, int> mp;
        mp.emplace(0, 1);
        int index = 0, n = nums.size(), sum = 0;
        for (; index < n && nums[index] != 0; ++index) {
            sum += nums[index];
            ++mp[sum];
        }
        int ans = 0;
        for (; index < n; ++index) {
            sum += nums[index];
            if (auto it = mp.find(sum); it != mp.end()) {
                ans += it->second;
            }
            if (auto it = mp.find(sum - 1); it != mp.end()) {
                ans += it->second;
            }
        }
        return ans;
    }
};
