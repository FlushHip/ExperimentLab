#include "headers.h"

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::unordered_map<int, int> ump;
        for (int num : nums) {
            ++ump[num];
        }
        std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>, std::greater<>>
            pri_que;
        for (auto [num, cnt] : ump) {
            pri_que.emplace(cnt, num);
            if (pri_que.size() > k) {
                pri_que.pop();
            }
        }
        std::vector<int> ans;
        while (!pri_que.empty()) {
            ans.push_back(pri_que.top().second);
            pri_que.pop();
        }
        return ans;
    }
};
