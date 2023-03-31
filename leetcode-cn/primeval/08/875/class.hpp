#include "headers.h"

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        auto fn = [&](int k) {
            int sum = 0;
            for (int pile : piles) {
                sum += (pile + k - 1) / k;
            }
            return sum <= h;
        };
        int lhs = 1, rhs = *std::max_element(piles.begin(), piles.end());
        while (lhs < rhs) {
            int mid = (lhs + rhs) / 2;
            if (!fn(mid)) {
                lhs = mid + 1;
            } else {
                rhs = mid;
            }
        }
        return lhs;
    }
};
