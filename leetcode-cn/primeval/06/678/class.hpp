class Solution {
public:
    bool checkValidString(string s) {
        dp_.clear();
        dp_.resize(s.size(), std::vector<int>(s.size(), 2));
        return dfs(s, 0, s.size() - 1);
    }

    bool dfs(const std::string &s, int l, int r) {
        if (l > r) {
            return true;
        }
        if (l == r) {
            return s[l] == '*';
        }
        if (dp_[l][r] != 2) {
            return dp_[l][r];
        }

        bool ans = false;
        if ((s[l] == '(' || s[l] == '*') && (s[r] == ')' || s[r] == '*')) {
            ans = dfs(s, l + 1, r - 1);
        }
        for (int i = l; !ans && i < r; ++i) {
            if (dfs(s, l, i) && dfs(s, i + 1, r)) {
                ans = true;
            }
        }
        return dp_[l][r] = ans;
    }

private:
    std::vector<std::vector<int>> dp_;
};
