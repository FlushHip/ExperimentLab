#include "headers.h"

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        auto cmp = [&nums](int lhs, int rhs) { return nums[lhs] < nums[rhs]; };
        std::priority_queue<int, std::vector<int>, decltype(cmp)> pri_que(cmp);
        std::vector<int> ans;
        int n = static_cast<int>(nums.size());
        ans.reserve(n - k + 1);
        for (int i = 0; i < n; ++i) {
            while (!pri_que.empty() && i - pri_que.top() + 1 > k) {
                pri_que.pop();
            }
            pri_que.emplace(i);
            if (i >= k - 1) {
                ans.emplace_back(nums[pri_que.top()]);
            }
        }
        return ans;
    }
};
