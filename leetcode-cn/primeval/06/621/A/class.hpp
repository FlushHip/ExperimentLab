#include "headers.h"

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        std::unordered_map<char, int> ump;
        for (auto c : tasks) {
            ++ump[c];
        }
        std::priority_queue<int> pri_que;
        for (auto [_, cnt] : ump) {
            pri_que.push(cnt);
        }

        int ans = 0;
        while (true) {
            std::vector<int> cache;
            int sum = 0;
            for (int i = 0; i < n + 1; ++i) {
                if (!pri_que.empty()) {
                    auto cnt = pri_que.top();
                    pri_que.pop();
                    --cnt;
                    if (cnt != 0) {
                        cache.push_back(cnt);
                    }
                    ++sum;
                }
            }
            if (!cache.empty()) {
                ans += n + 1;
                for (int num : cache) {
                    pri_que.emplace(num);
                }
            } else {
                ans += sum;
                if (pri_que.empty()) {
                    break;
                }
            }
        }
        return ans;
    }
};
