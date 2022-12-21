#include "headers.h"

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n,
        vector<vector<int>>& edgeList,
        vector<vector<int>>& queries) {
        auto cmp = [](const auto& lhs, const auto& rhs) {
            return lhs[2] < rhs[2];
        };
        std::sort(edgeList.begin(), edgeList.end(), cmp);
        for (int i = 0; i < queries.size(); ++i) {
            queries[i].push_back(i);
        }
        std::sort(queries.begin(), queries.end(), cmp);

        // build
        std::vector<int> pre(n);
        std::iota(pre.begin(), pre.end(), 0);
        std::function<int(int)> find = [&](int x) mutable {
            return pre[x] == x ? x : pre[x] = find(pre[x]);
        };
        int index = 0;

        std::vector<bool> ans(queries.size());
        for (const auto& qu : queries) {
            for (; index < edgeList.size() && edgeList[index][2] < qu[2];
                 ++index) {
                int x = find(edgeList[index][0]);
                int y = find(edgeList[index][1]);
                if (x != y) {
                    pre[x] = y;
                }
            }

            ans[qu[3]] = find(qu[0]) == find(qu[1]);
        }
        return ans;
    }
};
