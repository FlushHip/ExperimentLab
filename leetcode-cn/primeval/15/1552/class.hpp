#include "headers.h"

class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        std::sort(position.begin(), position.end());
        int lhs = 1, rhs = position.back() - position.front();
        auto fn = [&](int x) {
            int pre = position[0], sum = 1;
            for (int i = 1; i < position.size(); ++i) {
                if (position[i] >= pre + x) {
                    pre = position[i];
                    ++sum;
                }
            }
            return sum >= m;
        };
        while (lhs < rhs) {
            int mid = (lhs + rhs + 1) / 2;
            if (!fn(mid)) {
                rhs = mid - 1;
            } else {
                lhs = mid;
            }
        }
        return rhs;
    }
};
