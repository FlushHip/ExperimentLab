#include "headers.h"

class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size(), top = std::accumulate(nums.begin(), nums.end(), 0);

        std::transform(nums.begin(), nums.end(), nums.begin(),
            [&](int num) { return num * n - top; });
        std::unordered_set<int> lset;
        for (int mask = 1; mask < (1 << n / 2); ++mask) {
            int sum = 0;
            for (int i = 0; i < n / 2; ++i) {
                if (mask & (1 << i)) {
                    sum += nums[i];
                }
            }
            if (sum == 0) {
                return true;
            }
            lset.emplace(sum);
        }

        for (int mask = 1; mask < ((1 << n - n / 2) - 1); ++mask) {
            int sum = 0;
            for (int i = n / 2; i < n; ++i) {
                if (mask & (1 << i - n / 2)) {
                    sum += nums[i];
                }
            }
            if (sum == 0 || lset.find(-sum) != lset.end()) {
                return true;
            }
        }
        return false;
    }
};
