#include "headers.h"

class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        auto fn = [](const auto& nums1, const auto& nums2) {
            return nums1.size() & 1
                ? std::accumulate(nums2.begin(), nums2.end(), 0,
                      [](int init, int num) { return init ^ num; })
                : 0;
        };
        return fn(nums1, nums2) ^ fn(nums2, nums1);
    }
};
