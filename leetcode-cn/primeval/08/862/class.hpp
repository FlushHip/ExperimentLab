#include "headers.h"

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size(), ans = -1;
        std::vector<long long> pre_sums(n);
        pre_sums[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            pre_sums[i] = pre_sums[i - 1] + nums[i];
        }
        std::deque<int> dq;
        dq.push_back(-1);
        for (int i = 0; i < n; ++i) {
            while (!dq.empty() &&
                pre_sums[i] - (dq.front() == -1 ? 0 : pre_sums[dq.front()]) >=
                    k) {
                ans = std::min(static_cast<unsigned int>(i - dq.front()),
                    static_cast<unsigned int>(ans));
                dq.pop_front();
            }
            while (!dq.empty() &&
                pre_sums[i] <= (dq.back() == -1 ? 0 : pre_sums[dq.back()])) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        return ans;
    }
};
