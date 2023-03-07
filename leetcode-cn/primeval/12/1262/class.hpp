#include "headers.h"

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int sum = 0;
        std::vector<int> mod1, mod2;
        for (int num : nums) {
            if (num % 3 == 1) {
                mod1.push_back(num);
            } else if (num % 3 == 2) {
                mod2.push_back(num);
            }
            sum += num;
        }

        if (sum % 3 == 0) {
            return sum;
        }
        std::sort(mod1.begin(), mod1.end());
        std::sort(mod2.begin(), mod2.end());
        if (sum % 3 == 1) {
            bool f = false;
            int ans = sum + 1;
            if (mod1.size() >= 1) {
                ans = mod1[0];
                f = true;
            }
            if (mod2.size() >= 2) {
                ans = std::min(ans, mod2[0] + mod2[1]);
                f = true;
            }
            return !f ? 0 : sum - ans;
        }
        if (sum % 3 == 2) {
            bool f = false;
            int ans = sum + 1;
            if (mod2.size() >= 1) {
                ans = mod2[0];
                f = true;
            }
            if (mod1.size() >= 2) {
                ans = std::min(ans, mod1[0] + mod1[1]);
                f = true;
            }
            return !f ? 0 : sum - ans;
        }
        return {};
    }
};
