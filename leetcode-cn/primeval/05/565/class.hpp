#include "headers.h"

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int size = static_cast<int>(nums.size());
        int result = std::numeric_limits<int>::min();
        for (int i = 0; i < size; ++i) {
            int cnt = 0;
            for (int t = nums[i]; nums[i] < size; t = nums[i]) {
                ++cnt;
                nums[i] = size;
                i = t;
            }
            result = std::max(result, cnt);
        }
        return result;
    }
};
