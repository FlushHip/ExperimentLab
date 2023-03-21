#include "headers.h"

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        std::unordered_map<int, int> hash_map;
        for (int num : nums) {
            hash_map.emplace(num, num);
        }
        int ans = 0;
        for (int num : nums) {
            if (hash_map.find(num - 1) != hash_map.end()) {
                continue;
            }
            int right = hash_map[num];
            while (hash_map.find(right + 1) != hash_map.end()) {
                right = hash_map[right + 1];
            }
            hash_map[num] = right;
            ans = std::max(ans, right - num + 1);
        }
        return ans;
    }
};
