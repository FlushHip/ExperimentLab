#include "headers.h"

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        if (n == 1) {
            return 1;
        }
        std::unordered_map<int, int> umpTo, umpFrom;
        for (const auto& edge : trust) {
            ++umpTo[edge[1]];
            ++umpFrom[edge[0]];
        }
        auto itBegin = std::find_if(umpTo.begin(), umpTo.end(),
            [=](const auto& pr) { return pr.second == n - 1; });
        if (itBegin == umpTo.end()) {
            return -1;
        }
        auto itEnd = std::next(itBegin);
        for (; itEnd != umpTo.end(); ++itEnd) {
            if (itEnd->second == n - 1) {
                return -1;
            }
        }
        return umpFrom[itBegin->first] ? -1 : itBegin->first;
    }
};
