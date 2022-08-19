#include "headers.h"

class Solution {
public:
    int busyStudent(vector<int>& startTime,
        vector<int>& endTime,
        int queryTime) {
        return std::inner_product(startTime.begin(), startTime.end(),
            endTime.begin(), 0, std::plus<int>{},
            std::bind(std::logical_and<int>{},
                std::bind(
                    std::less_equal<int>{}, std::placeholders::_1, queryTime),
                std::bind(std::greater_equal<int>{}, std::placeholders::_2,
                    queryTime)));
    }
};
