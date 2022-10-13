#include "headers.h"

// TLE
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int const n = static_cast<int>(nums1.size());
        std::sort(nums1.begin(), nums1.end());
        for (int i = 0; i < n; ++i) {
            auto iter =
                std::lower_bound(nums1.begin() + i, nums1.end(), nums2[i] + 1);
            if (iter == nums1.end()) {
                continue;
            }
            for (int j = iter - nums1.begin(); j > i; --j) {
                std::swap(nums1[j], nums1[j - 1]);
            }
        }
        return nums1;
    }
};
