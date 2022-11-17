#include "headers.h"

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        std::copy(nums2.begin(), nums2.end(), nums1.begin() + m);
        inplace_merge(nums1, 0, m, m + n);
    }

private:
    void inplace_merge(std::vector<int>& line, int lhs, int mid, int rhs) {
        if (lhs == mid || mid == rhs) {
            return;
        }
        while (lhs < mid && line[lhs] <= line[mid]) {
            ++lhs;
        }
        if (lhs == mid) {
            return;
        }
        while (rhs >= mid && line[rhs - 1] >= line[mid - 1]) {
            --rhs;
        }
        if (rhs < mid) {
            return;
        }
        if (mid - lhs == 1 || rhs - mid == 1) {
            std::rotate(
                line.begin() + lhs, line.begin() + mid, line.begin() + rhs);
            return;
        }
        int left_mid = (mid + lhs) / 2;
        int right_mid = std::lower_bound(line.begin() + mid, line.begin() + rhs,
                            line[left_mid]) -
            line.begin();
        int next_mid = std::rotate(line.begin() + left_mid, line.begin() + mid,
                           line.begin() + right_mid) -
            line.begin();

        inplace_merge(line, lhs, left_mid, next_mid);
        inplace_merge(line, next_mid, right_mid, rhs);
    }
};
