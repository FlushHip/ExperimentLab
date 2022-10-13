#include "headers.h"

class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = static_cast<int>(nums1.size());
        std::vector<int> indexes(n);
        std::iota(indexes.begin(), indexes.end(), 0);
        std::sort(nums1.begin(), nums1.end());
        std::sort(indexes.begin(), indexes.end(),
            [&nums2](const int lhs, const int rhs) {
                return nums2[lhs] < nums2[rhs];
            });
        std::vector<int> ans(n);
        int lhs = 0, rhs = n - 1;
        for (int num : nums1) {
            ans[num > nums2[indexes[lhs]] ? indexes[lhs++] : indexes[rhs--]] =
                num;
        }
        return ans;
    }
};
