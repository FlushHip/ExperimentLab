#include <numeric>
#include "headers.h"

class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int sum = std::accumulate(nums.begin(), nums.end(), 0), now = 0;
        std::vector<int> result;
        for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
            result.push_back(*it);
            if ((now + *it) * 2 > sum) {
                break;
            }
            now += *it;
        }
        return result;
    }
};
