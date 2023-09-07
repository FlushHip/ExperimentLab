#include "headers.h"

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = static_cast<int>(intervals.size());
        std::sort(intervals.begin(), intervals.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[1] < rhs[1]; });
        int right = intervals[0][1], sum = 1;
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] >= right) {
                ++sum;
                right = intervals[i][1];
            }
        }
        return n - sum;
    }
};
