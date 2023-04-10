#include "headers.h"

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        std::stable_partition(
            nums.begin(), nums.end(), [](int num) { return num != 0; });
    }
};
