#include "headers.h"

class Solution {
public:
    int busyStudent(vector<int>& startTime,
        vector<int>& endTime,
        int queryTime) {
        std::sort(startTime.begin(), startTime.end());
        std::sort(endTime.begin(), endTime.end());
        return (std::upper_bound(
                    startTime.begin(), startTime.end(), queryTime) -
                   startTime.begin()) -
            (std::lower_bound(endTime.begin(), endTime.end(), queryTime) -
                endTime.begin());
    }
};
