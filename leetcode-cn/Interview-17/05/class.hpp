#include "headers.h"

class Solution {
public:
    vector<string> findLongestSubarray(vector<string>& array) {
        int n = static_cast<int>(array.size());
        std::unordered_map<int, int> ump;
        ump.emplace(0, -1);
        int max_len = 0, sum = 0;
        std::pair<int, int> interval;
        for (int i = 0; i < n; ++i) {
            sum += std::isdigit(array[i].front()) ? 1 : -1;
            if (auto it = ump.find(sum); it != ump.end()) {
                if (max_len < i - it->second) {
                    max_len = i - it->second;
                    interval = {it->second, i};
                }
            } else {
                ump.emplace(sum, i);
            }
        }
        return max_len == 0
            ? std::vector<std::string>{}
            : std::vector<std::string>{interval.first + 1 + array.begin(),
                  interval.second + 1 + array.begin()};
    }
};
