#include "headers.h"

class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        return static_cast<int>(
            std::min(std::count_if(position.begin(), position.end(),
                         [](int e) { return e % 2 == 0; }),
                std::count_if(position.begin(), position.end(),
                    [](int e) { return e % 2 != 0; })));
    }
};
