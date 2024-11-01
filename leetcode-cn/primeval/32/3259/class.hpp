#include "headers.h"

class Solution {
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA,
        vector<int>& energyDrinkB) {
        int n = static_cast<int>(energyDrinkA.size());
        assert(n >= 3);
        std::array<std::vector<long long>, 2> dp{};
        dp.fill(std::vector<long long>(n));
        dp[0][0] = energyDrinkA[0];
        dp[1][0] = energyDrinkB[0];
        for (int i = 1; i < n; ++i) {
            dp[0][i] = std::max(dp[0][i - 1] + energyDrinkA[i], dp[1][i - 1]);
            dp[1][i] = std::max(dp[1][i - 1] + energyDrinkB[i], dp[0][i - 1]);
        }
        return std::max(dp[0][n - 1], dp[1][n - 1]);
    }
};
