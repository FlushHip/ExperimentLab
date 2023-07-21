#include "headers.h"

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        int n = static_cast<int>(points.size());
        int ans = std::numeric_limits<int>::min();
        auto cmp = [&points](int lhs, int rhs) {
            return points[lhs][1] - points[lhs][0] <
                points[rhs][1] - points[rhs][0];
        };
        std::priority_queue<int, std::vector<int>, decltype(cmp)> pri_que(cmp);
        pri_que.emplace(0);
        for (int i = 1; i < n; ++i) {
            while (!pri_que.empty() &&
                points[i][0] - points[pri_que.top()][0] > k) {
                pri_que.pop();
            }
            if (!pri_que.empty()) {
                ans = std::max(ans,
                    points[i][0] + points[i][1] + points[pri_que.top()][1] -
                        points[pri_que.top()][0]);
            }
            pri_que.emplace(i);
        }
        return ans;
    }
};
