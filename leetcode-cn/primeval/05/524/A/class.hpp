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

        for (const auto &word : dictionary) {
            if (isSubsequence(s, word)) {
                return word;
            }
        }
        return ""s;
    }

    // TAG : 判断一个序列是否是另一个序列的子序列
    bool isSubsequence(const std::string &sequence, const std::string &sub) {
        int index = 0;
        for (int i = 0; i < (int)sequence.size()
            && index < (int)sub.size(); ++i) {
            if (sequence[i] == sub[index]) {
                ++index;
            }
        }
        return index == (int)sub.size();
    }
};
