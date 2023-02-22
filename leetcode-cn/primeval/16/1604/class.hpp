#include "headers.h"

class Solution {
public:
    vector<string> alertNames(vector<string>& keyName,
        vector<string>& keyTime) {
        int n = keyName.size();
        std::unordered_map<std::string, std::vector<int>> mp;
        for (int i = 0; i < n; ++i) {
            int h = 0, m = 0;
            (void)std::sscanf(keyTime[i].c_str(), "%d:%d", &h, &m);
            mp[keyName[i]].emplace_back(h * 60 + m);
        }

        std::vector<std::string> ans;
        for (auto&& [name, hours] : mp) {
            std::sort(hours.begin(), hours.end());
            int lhs = 0, rhs = 0, top = hours.size();
            for (; rhs < top; ++rhs) {
                while (hours[rhs] - hours[lhs] > 60) {
                    ++lhs;
                }
                if (rhs - lhs + 1 >= 3) {
                    ans.push_back(name);
                    break;
                }
            }
        }
        std::sort(ans.begin(), ans.end());

        return ans;
    }
};
