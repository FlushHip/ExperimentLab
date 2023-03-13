#include "headers.h"

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        long long top = 1LL << n;
        std::vector<std::vector<int>> ans;
        for (long long i = 0; i < top; ++i) {
            std::bitset<10> bits(i);
            std::vector<int> line;
            bool f = false;
            for (int k = 0; k < n; ++k) {
                if (k - 1 >= 0 && bits.test(k) && !bits.test(k - 1) &&
                    nums[k] == nums[k - 1]) {
                    f = true;
                    break;
                }
                if (bits.test(k)) {
                    line.push_back(nums[k]);
                }
            }
            if (!f) {
                ans.push_back(std::move(line));
            }
        }
        return ans;
    }
};
