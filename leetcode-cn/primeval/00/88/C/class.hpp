#include "headers.h"

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index = m + n - 1, lhs = m - 1, rhs = n - 1;
        while (lhs >= 0 && rhs >= 0) {
            if (nums1[lhs] > nums2[rhs]) {
                nums1[index--] = nums1[lhs--];
            } else {
                nums1[index--] = nums2[rhs--];
            }
        }
        while (rhs >= 0) {
            nums1[index--] = nums2[rhs--];
        }
    }
};
