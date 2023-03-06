#include "headers.h"

class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        std::vector<string> ans;
        ans.reserve(names.size());
        std::unordered_map<std::string_view, int> mp;
        for (std::string_view name : names) {
            if (auto it = mp.find(name); it == mp.end()) {
                ans.emplace_back(name);
                mp[name] = 1;
            } else {
                std::string str;
                do {
                    str = std::string(name) + "(" + std::to_string(mp[name]) +
                        ")";
                    ++mp[name];
                } while (mp.find(str) != mp.end());
                ans.push_back(std::move(str));
                mp[ans.back()] = 1;
            }
        }
        return ans;
    }
};
