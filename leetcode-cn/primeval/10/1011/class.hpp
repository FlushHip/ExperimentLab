#include "headers.h"

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        auto fn = [&weights](int w) {
            int ret = 0, sum = 0;
            for (auto weight : weights) {
                if (sum + weight <= w) {
                    sum += weight;
                } else {
                    ++ret;
                    sum = weight;
                }
            }
            if (sum) {
                ++ret;
            }
            return ret;
        };
        int lhs = *std::max_element(weights.begin(), weights.end()),
            rhs = std::reduce(weights.begin(), weights.end());
        while (lhs < rhs) {
            int mid = (lhs + rhs) / 2;
            if (fn(mid) > days) {
                lhs = mid + 1;
            } else {
                rhs = mid;
            }
        }
        return lhs;
    }
};
