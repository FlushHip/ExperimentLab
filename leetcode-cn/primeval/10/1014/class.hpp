#include "headers.h"

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int ans = 0, max_value = values[0] + 0,
            n = static_cast<int>(values.size());
        for (int i = 1; i < n; ++i) {
            ans = std::max(ans, values[i] - i + max_value);
            max_value = std::max(max_value, values[i] + i);
        }
        return ans;
    }
};
