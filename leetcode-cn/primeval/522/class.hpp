class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        std::map<std::size_t, std::unordered_map<std::string, int>> mp;
        for (const auto &str : strs) {
            ++mp[str.size()][str];
        }
        auto cmp = [](const std::string &m, const std::string &sub)
        {
            auto itB = sub.cbegin();
            for (auto itA = m.cbegin(); itA != m.cend() && itB != sub.cend(); ++itA) {
                if (*itA == *itB) {
                    ++itB;
                }
            }
            return itB == sub.cend();
        };
        for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
            auto theLast = it->second;
            for (auto iter = theLast.begin(); iter != theLast.end(); ++iter) {
                if (iter->second != 1) {
                    continue;
                }
                bool f = true;
                for (auto iA = mp.rbegin(); iA != it && f; ++iA) {
                    for (auto iB = iA->second.begin(); iB != iA->second.end() && f; ++iB) {
                        if (cmp(iB->first, iter->first)) {
                            f = false;
                        }
                    }
                }
                if (f) {
                    return (int)it->first;
                }
            }
        }
        return -1;
    }
};
