#include "headers.h"

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        auto [min_value, max_value] =
            std::minmax_element(nums.begin(), nums.end());
        int offset = -*min_value;
        int top = offset + *max_value + 1;
        std::vector<int> line(top, 0);
        for (int num : nums) {
            ++line[num + offset];
        }
        for (int i = top - 1; i >= 0; --i) {
            if (k - line[i] <= 0) {
                return i - offset;
            }
            k -= line[i];
        }
        return 0;
    }
};
