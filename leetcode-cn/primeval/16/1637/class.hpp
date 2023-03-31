#include "headers.h"

class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        std::sort(points.begin(), points.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[0] < rhs[0]; });
        int ans = 0, n = static_cast<int>(points.size());
        for (int i = 1; i < n; ++i) {
            ans = std::max(ans, points[i][0] - points[i - 1][0]);
        }
        return ans;
    }
};
