#include "headers.h"

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int size = static_cast<int>(tasks.size());
        std::unordered_map<char, int> ump;
        for (auto c : tasks) {
            ++ump[c];
        }
        int h = std::max_element(
            ump.begin(), ump.end(), [](const auto& lhs, const auto& rhs) {
                return lhs.second < rhs.second;
            })->second;
        int rest = std::accumulate(ump.begin(), ump.end(), 0,
            [h](const auto& result, const auto& ele) {
                return result + (ele.second == h);
            });
        return std::max(size, (h - 1) * (n + 1) + rest);
    }
};
