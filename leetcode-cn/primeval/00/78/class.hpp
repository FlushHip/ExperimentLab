#include "headers.h"

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        long long top = 1LL << n;
        std::vector<std::vector<int>> ans;
        for (long long i = 0; i < top; ++i) {
            std::bitset<10> bits(i);
            std::vector<int> line;
            for (int k = 0; k < n; ++k) {
                if (bits.test(k)) {
                    line.push_back(nums[k]);
                }
            }
            ans.push_back(std::move(line));
        }
        return ans;
    }
};
