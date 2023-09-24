#include <memory>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>

#include <dbg.h>

class Solution {
public:
    int maximumScore(std::vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        std::sort(nums.begin(), nums.end());
        int last = nums.back() + 2 * k;
        std::vector<int> line(last + 2, 0);
        for (int i = 0; i < n; ++i) {
            ++line[nums[i]];
            --line[nums[i] + 2 * k + 1];
        }
        std::partial_sum(line.begin(), line.end(), line.begin());
        dbg(line);
        return *std::max_element(line.begin(), line.end());
    }
};
