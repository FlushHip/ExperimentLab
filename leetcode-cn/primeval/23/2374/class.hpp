#include "headers.h"

class Solution {
public:
    int edgeScore(vector<int>& edges) {
        int n = static_cast<int>(edges.size());
        std::vector<uint64_t> line(n, 0);
        for (int i = 0; i < n; ++i) {
            line[edges[i]] += i;
        }
        return std::max_element(line.begin(), line.end()) - line.begin();
    }
};
