#include "headers.h"

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals,
        vector<int>& newInterval) {
        auto it_lhs =
            std::lower_bound(intervals.begin(), intervals.end(), newInterval[0],
                [](auto&& lhs, auto&& rhs) { return lhs[1] < rhs; });
        auto it_rhs =
            std::upper_bound(intervals.begin(), intervals.end(), newInterval[1],
                [](auto&& lhs, auto&& rhs) { return lhs < rhs[0]; });
        std::vector<std::vector<int>> ans;
        for (auto it = intervals.begin(); it != it_lhs; ++it) {
            ans.push_back(*it);
        }
        int i_left = std::min(newInterval[0],
            it_lhs == intervals.end() ? std::numeric_limits<int>::max()
                                      : (*it_lhs)[0]);
        int i_right = std::max(newInterval[1],
            it_rhs == intervals.begin() ? std::numeric_limits<int>::min()
                                        : (*std::prev(it_rhs))[1]);
        ans.push_back({i_left, i_right});
        for (auto it = it_rhs; it != intervals.end(); ++it) {
            ans.push_back(*it);
        }
        return ans;
    }
};
