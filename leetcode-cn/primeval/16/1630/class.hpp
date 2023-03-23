#include "headers.h"

class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums,
        vector<int>& l,
        vector<int>& r) {
        int m = static_cast<int>(l.size());
        std::vector<bool> ans;
        ans.reserve(m);
        for (int i = 0; i < m; ++i) {
            int lhs = l[i], rhs = r[i];
            auto [min_it, max_it] =
                std::minmax_element(nums.begin() + lhs, nums.begin() + rhs + 1);
            if (*max_it == *min_it) {
                ans.push_back(true);
                continue;
            }
            if ((*max_it - *min_it) % (rhs - lhs) != 0) {
                ans.push_back(false);
                continue;
            }
            int d = (*max_it - *min_it) / (rhs - lhs);
            std::unordered_set<int> used;
            bool f = true;
            for (int i = lhs; i <= rhs; ++i) {
                if ((nums[i] - *min_it) % d != 0) {
                    f = false;
                    break;
                }
                int index = (nums[i] - *min_it) / d;
                if (used.find(index) != used.end()) {
                    f = false;
                    break;
                }
                used.emplace(index);
            }
            ans.push_back(f);
        }
        return ans;
    }
};
