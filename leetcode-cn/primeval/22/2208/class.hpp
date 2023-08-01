#include "headers.h"

class Solution {
public:
    int halveArray(vector<int>& nums) {
        std::priority_queue<double> pri_que;
        double t_sum = 0;
        for (int& num : nums) {
            pri_que.emplace(num);
            t_sum += num;
        }
        int ans = 0;
        for (double sum = 0; !pri_que.empty() && sum * 2 < t_sum;) {
            auto num = pri_que.top() / 2;
            pri_que.pop();
            ++ans;
            sum += num;
            pri_que.emplace(num);
        }
        return ans;
    }
};
