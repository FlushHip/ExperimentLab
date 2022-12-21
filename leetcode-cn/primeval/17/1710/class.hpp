#include "headers.h"

class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        std::sort(boxTypes.begin(), boxTypes.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[1] > rhs[1]; });
        int ans = 0, cnt = 0;
        for (const auto& box : boxTypes) {
            if (cnt + box[0] <= truckSize) {
                ans += box[1] * box[0];
                cnt += box[0];
            } else {
                ans += (truckSize - cnt) * box[1];
                break;
            }
        }
        return ans;
    }
};
