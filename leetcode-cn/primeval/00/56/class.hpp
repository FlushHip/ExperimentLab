#include "headers.h"

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        std::vector<std::vector<int>> ans;
        std::sort(intervals.begin(), intervals.end(),
            [](const auto& lhs, const auto& rhs) {
                return lhs[0] == rhs[0] ? lhs[1] < rhs[1] : lhs[0] < rhs[0];
            });
        int last_lhs = intervals[0][0], last_rhs = intervals[0][1];
        int n = static_cast<int>(intervals.size());
        for (int i = 1; i < n; ++i) {
            if (last_lhs <= intervals[i][0] && intervals[i][0] <= last_rhs) {
                if (intervals[i][1] > last_rhs) {
                    last_rhs = intervals[i][1];
                }
            } else {
                ans.emplace_back(std::vector<int>{last_lhs, last_rhs});
                std::tie(last_lhs, last_rhs) = {
                    intervals[i][0], intervals[i][1]};
            }
        }
        ans.emplace_back(std::vector<int>{last_lhs, last_rhs});

        return ans;
    }
};
