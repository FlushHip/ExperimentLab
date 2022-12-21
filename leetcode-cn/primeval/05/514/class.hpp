#include "headers.h"

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int ring_size = ring.size(), n = key.size();
        std::array<std::vector<int>, 26> alpha_index;
        for (int i = 0; i < ring_size; ++i) {
            alpha_index[ring[i] - 'a'].push_back(i);
        }
        std::vector<std::vector<int>> dp(
            n, std::vector<int>(ring_size, std::numeric_limits<int>::max()));
        for (auto index : alpha_index[key[0] - 'a']) {
            dp[0][index] = 1 + std::min(ring_size - index, index);
        }
        for (int i = 1; i < n; ++i) {
            for (auto index_now : alpha_index[key[i] - 'a']) {
                for (auto index_pre : alpha_index[key[i - 1] - 'a']) {
                    dp[i][index_now] = std::min(dp[i][index_now],
                        1 + dp[i - 1][index_pre] +
                            std::min(std::abs(index_now - index_pre),
                                ring_size - std::abs(index_now - index_pre)));
                }
            }
        }
        return *std::min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};
