class Solution {
    bool dfs(std::string_view s, std::string_view p, unsigned is, unsigned ip) {
        if (is == s.size() && ip == p.size()) {
            return true;
        }
        if (is != s.size() && ip == p.size()) {
            return false;
        }
        if (ip + 1 < p.size() && p[ip + 1] == '*') {
            if (dfs(s, p, is, ip + 2)) {
                return true;
            }
            for (int i = 0; is + i < s.size(); ++i) {
                if (p[ip] != '.' && p[ip] != s[is + i]) {
                    break;
                }
                if (dfs(s, p, is + i + 1, ip + 2)) {
                    return true;
                }
            }
            return false;
        }
        if (is == s.size()) {
            return false;
        }
        if (p[ip] != '.' && p[ip] != s[is]) {
            return false;
        }
        return dfs(s, p, is + 1, ip + 1);
    }
public:
    bool isMatch(string s, string p) {
        return dfs(s, p, 0u, 0u);
    }
};
