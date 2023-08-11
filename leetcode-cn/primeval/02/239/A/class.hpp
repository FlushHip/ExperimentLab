#include "headers.h"

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        std::deque<int> que;
        std::vector<int> ans;
        int n = static_cast<int>(nums.size());
        ans.reserve(n - k + 1);
        for (int i = 0; i < n; ++i) {
            while (!que.empty() && i - que.front() + 1 > k) {
                que.pop_front();
            }
            while (!que.empty() && nums[que.back()] <= nums[i]) {
                que.pop_back();
            }
            que.push_back(i);
            if (i >= k - 1) {
                ans.emplace_back(nums[que.front()]);
            }
        }
        return ans;
    }
};
