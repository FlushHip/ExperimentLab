#include "headers.h"

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        std::sort(
            people.begin(), people.end(), [](const auto& lhs, const auto& rhs) {
                return lhs[0] == rhs[0] ? lhs[1] > rhs[1] : lhs[0] < rhs[0];
            });
        std::vector<bool> used(people.size(), false);
        std::vector<std::vector<int>> ans(people.size());
        int n = static_cast<int>(people.size());
        for (auto& p : people) {
            int i = 0;
            for (int cnt = 0; i < n; ++i) {
                if (!used[i]) {
                    ++cnt;
                }
                if (cnt == p[1] + 1) {
                    break;
                }
            }
            ans[i] = std::move(p);
            used[i] = true;
        }
        return ans;
    }
};
