#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

#include <dbg.h>

class Solution {
public:
    int subsequence(std::string source, std::string pattern) {
        int ans = 0;
        dfs(source, 0, pattern, 0, ans);
        return ans;
    }

private:
    void dfs(const std::string& source,
        size_t i,
        const std::string& pattern,
        size_t j,
        int& ans) {
        if (j == pattern.size()) {
            ++ans;
            return;
        }
        if (i == source.size()) {
            return;
        }
        for (auto idx = i; idx < source.size(); ++idx) {
            if (source[idx] == pattern[j]) {
                dfs(source, idx + 1, pattern, j + 1, ans);
            }
        }
    }
};
