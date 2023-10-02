#include "headers.h"

class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        struct context_t {
            int plant_time;
            int grow_time;
        };
        int n = static_cast<int>(plantTime.size());
        std::vector<context_t> ctxs;
        for (int i = 0; i < n; ++i) {
            ctxs.emplace_back(context_t{plantTime[i], growTime[i]});
        }
        std::sort(ctxs.begin(), ctxs.end(), [](auto&& lhs, auto&& rhs) {
            return lhs.grow_time == rhs.grow_time
                ? lhs.plant_time > rhs.plant_time
                : lhs.grow_time > rhs.grow_time;
        });
        long long ans = 0LL, sum = 0LL;
        for (int i = 0; i < n; ++i) {
            sum += ctxs[i].plant_time;
            ans = std::max(ans, sum + ctxs[i].grow_time + 1);
        }
        return ans - 1;
    }
};
