#include "headers.h"

// std::regex TLE
class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        std::unordered_map<std::string, std::string> hash_map;
        for (const auto& element : knowledge) {
            hash_map[element[0]] = element[1];
        }
        std::string ans;
        std::regex rg("\\([a-z]+\\)");
        for (std::smatch backet_match;
             std::regex_search(s, backet_match, rg) && !s.empty();
             s = backet_match.suffix()) {
            ans.append(backet_match.prefix());
            auto key = backet_match[0].str().substr(
                1, backet_match[0].str().size() - 2);
            if (hash_map.count(key)) {
                ans.append(hash_map[key]);
            } else {
                ans.append("?");
            }
        }
        return ans.append(s);
    }
};
