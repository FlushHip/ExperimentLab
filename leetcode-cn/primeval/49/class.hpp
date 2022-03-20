class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> mp;
        for (auto &str : strs) {
            auto str_sorted(str);
            std::sort(str_sorted.begin(), str_sorted.end());
            mp[str_sorted].emplace_back(str);
        }
        std::vector<std::vector<string>> ans;
        for (auto &&[_, v] : mp) {
            ans.emplace_back(v);
        }
        return ans;
    }
};
