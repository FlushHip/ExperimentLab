#include "headers.h"

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = static_cast<int>(s.size());
        std::array<int, 26> last{};
        for (int i = 0; i < n; ++i) {
            last[s[i] - 'a'] = i;
        }
        int start = 0, end = 0;
        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            end = std::max(end, last[s[i] - 'a']);
            if (i == end) {
                ans.emplace_back(end - start + 1);
                start = i + 1;
            }
        }
        return ans;
    }
};
