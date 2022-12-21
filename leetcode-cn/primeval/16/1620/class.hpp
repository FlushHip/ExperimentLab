#include "headers.h"

class Solution {
public:
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        auto [x_lhs, x_rhs] = std::minmax_element(towers.begin(), towers.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[0] < rhs[0]; });
        auto [y_dhs, y_uhs] = std::minmax_element(towers.begin(), towers.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[1] < rhs[1]; });

        std::vector<int> ans{0, 0};
        int sum = 0;
        for (int x = x_lhs->at(0); x <= x_rhs->at(0); ++x) {
            for (int y = y_dhs->at(1); y <= y_uhs->at(1); ++y) {
                int tmp = std::accumulate(towers.begin(), towers.end(), 0,
                    [x, y, radius](int res, const std::vector<int>& tower) {
                        int d2 = (tower[0] - x) * (tower[0] - x) +
                            (tower[1] - y) * (tower[1] - y);
                        return d2 > radius * radius ? res
                                                    : res +
                                static_cast<int>(
                                    tower[2] / (1 + std::sqrt(d2)));
                    });
                if (tmp > sum) {
                    sum = tmp;
                    ans = {x, y};
                }
            }
        }
        return ans;
    }
};
