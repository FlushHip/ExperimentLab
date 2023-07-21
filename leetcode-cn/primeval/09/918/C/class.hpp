#include "headers.h"

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        struct context {
            int index;
            int sum;
        };
        std::deque<context> dque;
        int ans = 0, sum = 0;
        dque.push_back({0, nums[0]});
        ans = sum = nums[0];
        for (int i = 1; i < 2 * n; ++i) {
            while (!dque.empty() && dque.front().index < i - n) {
                dque.pop_front();
            }
            sum += nums[i % n];
            ans = std::max(ans, dque.empty() ? sum : sum - dque.front().sum);
            while (!dque.empty() && dque.back().sum >= sum) {
                dque.pop_back();
            }
            dque.push_back({i, sum});
        }
        return ans;
    }
};
