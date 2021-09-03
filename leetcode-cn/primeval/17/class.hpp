class Solution {
public:
    Solution() {
        maps_[2] = "abc";
        maps_[3] = "def";
        maps_[4] = "ghi";
        maps_[5] = "jkl";
        maps_[6] = "mno";
        maps_[7] = "pqrs";
        maps_[8] = "tuv";
        maps_[9] = "wxyz";
    }
    vector<string> letterCombinations(string digits) {
        ans_.clear();
        if (!digits.size()) {
            return ans_;
        }
        std::string str;
        dfs(digits, 0, str);
        return ans_;
    }
    void dfs(const std::string &digits, unsigned int index, std::string &str) {
        if (index == digits.size()) {
            ans_.push_back(str);
            return ;
        }
        for (const auto c : maps_[digits[index] - '0']) {
            str.push_back(c);
            dfs(digits, index + 1, str);
            str.pop_back();
        }
    }
private:
    std::unordered_map<int, std::string> maps_;
    std::vector<std::string> ans_;
};
