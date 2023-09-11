#include "headers.h"

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = static_cast<int>(points.size());
        std::sort(points.begin(), points.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[1] < rhs[1]; });
        int right = points[0][1], ans = 1;
        for (int i = 1; i < n; ++i) {
            if (right >= points[i][0]) {
                continue;
            }
            right = points[i][1];
            ++ans;
        }
        return ans;
    }
};
