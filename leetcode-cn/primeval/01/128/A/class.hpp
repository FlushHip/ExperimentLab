#include "headers.h"

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        std::unordered_set<int> hash_set(nums.begin(), nums.end());
        int ans = 0;
        for (int num : nums) {
            if (hash_set.find(num - 1) != hash_set.end()) {
                continue;
            }
            int sum = 1;
            for (; hash_set.find(num + sum) != hash_set.end(); ++sum) {
            }
            ans = std::max(ans, sum);
        }
        return ans;
    }
};
