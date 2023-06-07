#include "headers.h"

class Solution {
public:
    int nthUglyNumber(int n) {
        std::unordered_set<long long> ust{1};
        std::priority_queue<long long, std::vector<long long>, std::greater<>>
            pri_que;
        pri_que.push(1);
        for (int i = 1; i < n; ++i) {
            auto ith = pri_que.top();
            pri_que.pop();
            for (auto d : {2, 3, 5}) {
                auto next = ith * d;
                if (!ust.count(next)) {
                    ust.emplace(next);
                    pri_que.emplace(next);
                }
            }
        }
        return pri_que.top();
    }
};
