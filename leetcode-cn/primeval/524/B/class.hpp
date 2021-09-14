class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        std::sort(dictionary.begin(), dictionary.end()
            , [](const auto &lhs, const auto &rhs)
        {
            return lhs.size() == rhs.size()
                ? lhs < rhs
                : lhs.size() > rhs.size();
        });

        build(s);
        for (const auto &word : dictionary) {
            if (isSubsequence(word)) {
                return word;
            }
        }
        return ""s;
    }

    void build(const std::string &sequence) {
        dp_.clear();
        int n = (int)sequence.size();
        dp_.resize(n + 1, std::vector<int>(26, -1));
        for (int i = n - 1; i >= 0; --i) {
            for (int c = 0; c < 26; ++c) {
                dp_[i][c] = dp_[i + 1][c];
            }
            dp_[i][sequence[i] - 'a'] = i;
        }
    }

    // TAG : 优化 - 序列自动机
    bool isSubsequence(const std::string &sub) {
        int n = (int)sub.size(), index = 0;
        for (int i = 0; i < n; ++i) {
            if (dp_[index][sub[i] - 'a'] == -1) {
                return false;
            }
            index = dp_[index][sub[i] - 'a'] + 1;
        }
        return true;
    }

private:
    std::vector<std::vector<int>> dp_;
};
