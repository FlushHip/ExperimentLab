#include "headers.h"

class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        std::sort(arr.begin(), arr.end());
        std::vector<int> sums(arr.size());
        std::partial_sum(arr.begin(), arr.end(), sums.begin());
        int lhs = 0, rhs = arr.back();
        auto fn = [&](int x) -> int {
            int index =
                std::lower_bound(arr.begin(), arr.end(), x) - arr.begin();
            return (index == 0 ? 0 : sums[index - 1]) +
                (arr.size() - index) * x;
        };
        while (lhs < rhs) {
            int mid = (lhs + rhs + 1) / 2;
            if (fn(mid) > target) {
                rhs = mid - 1;
            } else {
                lhs = mid;
            }
        }
        if (std::abs(fn(lhs) - target) > std::abs(fn(lhs + 1) - target)) {
            ++lhs;
        }
        return lhs;
    }
};
