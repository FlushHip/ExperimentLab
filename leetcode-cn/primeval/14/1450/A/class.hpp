#include "headers.h"

class Solution {
public:
    int busyStudent(vector<int>& startTime,
        vector<int>& endTime,
        int queryTime) {
        auto top = *std::max_element(endTime.begin(), endTime.end());
        int n = static_cast<int>(startTime.size());
        if (queryTime > top) {
            return 0;
        }
        std::vector<int> buff(top + 1 + 1, 0);
        for (int i = 0; i < n; ++i) {
            ++buff[startTime[i]];
            --buff[endTime[i] + 1];
        }
        return std::accumulate(buff.begin(), buff.begin() + 1 + queryTime, 0);
    }
};
