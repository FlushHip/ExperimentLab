#include "headers.h"

class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() * 6 < nums2.size() ||
            nums1.size() > 6 * nums2.size()) {
            return -1;
        }
        int sum1 = std::accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = std::accumulate(nums2.begin(), nums2.end(), 0);
        if (sum1 < sum2) {
            std::swap(nums1, nums2);
            std::swap(sum1, sum2);
        }
        int d = sum1 - sum2;
        std::vector<int> offset(6, 0);
        for (int num : nums1) {
            ++offset[num - 1];
        }
        for (int num : nums2) {
            ++offset[6 - num];
        }
        int ans = 0;
        for (int i = 5; i > 0 && d; --i) {
            if (i * offset[i] >= d) {
                ans += (d + i - 1) / i;
                break;
            }
            d -= i * offset[i];
            ans += offset[i];
        }
        return ans;
    }
};
