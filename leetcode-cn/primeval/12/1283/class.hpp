#include "headers.h"

class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        auto fn = [&nums](int k) {
            return std::accumulate(nums.begin(), nums.end(), 0,
                [k](int last, int num) { return last + (num + k - 1) / k; });
        };
        int lhs = 1, rhs = *std::max_element(nums.begin(), nums.end());
        while (lhs < rhs) {
            int mid = (lhs + rhs) / 2;
            if (fn(mid) <= threshold) {
                rhs = mid;
            } else {
                lhs = mid + 1;
            }
        }
        return lhs;
    }
};
