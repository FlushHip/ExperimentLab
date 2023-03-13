#include "headers.h"

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ans = 0, cnt = 0;
        for (int num : nums) {
            if (cnt == 0) {
                ans = num;
                cnt = 1;
            } else if (num == ans) {
                ++cnt;
            } else {
                --cnt;
            }
        }
        return ans;
    }
};
