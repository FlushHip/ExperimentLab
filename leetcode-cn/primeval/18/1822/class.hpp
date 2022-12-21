#include "headers.h"

class Solution {
public:
    int arraySign(vector<int>& nums) {
        if (std::any_of(
                nums.begin(), nums.end(), [](int num) { return num == 0; })) {
            return 0;
        }
        return std::count_if(
                   nums.begin(), nums.end(), [](int num) { return num < 0; }) %
                2
            ? -1
            : 1;
    }
};
