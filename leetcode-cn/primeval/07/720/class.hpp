class Solution {
public:
    string longestWord(vector<string>& words) {
        std::map<std::size_t, std::set<std::string, std::greater<std::string>>> size_map;
        for (const auto &word : words) {
            size_map[word.size()].emplace(word);
        }

        std::string ans;
        std::set<std::string> lines{ ""s };
        for (const auto &[len, strs] : size_map) {
            for (const auto &str : strs) {
                if (lines.find(str.substr(0, len - 1)) != lines.end()) {
                    lines.emplace(str);
                    ans = str;
                }
            }
        }
        return ans;
    }
};
