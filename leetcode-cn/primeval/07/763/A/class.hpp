#include "headers.h"

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = static_cast<int>(s.size());
        std::array<std::vector<int>, 26> pre;
        pre.fill(std::vector<int>(n, 0));
        pre[s[0] - 'a'][0] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 26; ++j) {
                pre[j][i] = pre[j][i - 1];
            }
            ++pre[s[i] - 'a'][i];
        }
        std::vector<int> ans;
        int sum = 0;
        std::unordered_set<char> last;
        for (int i = 0; i < n; ++i) {
            last.emplace(s[i] - 'a');
            ++sum;
            if (pre[s[i] - 'a'][n - 1] == pre[s[i] - 'a'][i]) {
                last.erase(s[i] - 'a');
                if (last.empty()) {
                    ans.emplace_back(sum);
                    sum = 0;
                }
            }
        }
        return ans;
    }
};
