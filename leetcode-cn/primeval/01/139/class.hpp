#include "headers.h"

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int max_length = 0;
        std::unordered_set<std::string_view> hash_set;
        for (const auto& word : wordDict) {
            max_length = std::max(max_length, static_cast<int>(word.size()));
            hash_set.insert(word);
        }
        int n = static_cast<int>(s.size());
        std::vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 0; i < n; ++i) {
            for (int j = std::max(0, i - max_length + 1); j <= i; ++j) {
                if (dp[j] &&
                    hash_set.find({s.data() + j,
                        static_cast<std::string_view::size_type>(i - j + 1)}) !=
                        hash_set.end()) {
                    dp[i + 1] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
