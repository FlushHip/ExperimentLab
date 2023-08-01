#include "headers.h"

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        int n = static_cast<int>(points.size());
        std::deque<int> dque;
        dque.push_back(0);
        int ans = std::numeric_limits<int>::min();
        for (int i = 1; i < n; ++i) {
            while (
                !dque.empty() && points[i][0] - points[dque.front()][0] > k) {
                dque.pop_front();
            }
            if (!dque.empty()) {
                ans = std::max(ans,
                    points[i][0] + points[i][1] + points[dque.front()][1] -
                        points[dque.front()][0]);
            }
            while (!dque.empty() &&
                points[dque.back()][1] - points[dque.back()][0] <=
                    points[i][1] - points[i][0]) {
                dque.pop_back();
            }
            dque.push_back(i);
        }
        return ans;
    }
};
