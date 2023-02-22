#include "headers.h"

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        std::unordered_map<std::string, std::string> hash_map;
        for (const auto& element : knowledge) {
            hash_map[element[0]] = element[1];
        }
        std::string ans;
        for (std::size_t begin = 0; begin != s.size();) {
            size_t lhs = s.find('(', begin);
            ans.append(s.begin() + begin,
                lhs == std::string::npos ? s.end() : s.begin() + lhs);
            if (lhs == std::string::npos) {
                break;
            }
            size_t rhs = s.find(')', lhs);
            std::string key(s.begin() + lhs + 1, s.begin() + rhs);
            if (hash_map.count(key)) {
                ans.append(hash_map[key]);
            } else {
                ans.append("?");
            }
            begin = rhs + 1;
        }
        return ans;
    }
};
