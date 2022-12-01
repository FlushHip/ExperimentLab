#include "headers.h"

class Solution {
public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        unsigned ans = -1, index = 0, ret = -1;
        for (auto& point : points) {
            if ((x == point[0] || y == point[1]) &&
                ans >
                    (unsigned)std::abs(x - point[0]) + std::abs(y - point[1])) {
                ans = (unsigned)std::abs(x - point[0]) + std::abs(y - point[1]);
                ret = index;
            }
            ++index;
        }
        return ret;
    }
};
