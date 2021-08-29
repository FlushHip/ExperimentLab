class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        std::vector<std::pair<int, int>> lines;
        std::transform(mat.begin(), mat.end()
            , std::back_inserter(lines)
            , [index = 0](const auto & line) mutable
            {
                return std::make_pair(
                    std::count(line.begin(), line.end(), 1),
                    index++);
            });
        std::sort(lines.begin(), lines.end()
            , [](const auto & lhs, const auto & rhs)
            {
                return lhs < rhs;
            });
        lines.erase(lines.begin() + k, lines.end());

        std::vector<int> ans;
        std::transform(lines.begin(), lines.end()
            , std::back_inserter(ans)
            , [](const auto line)
            {
                return line.second;
            });

        return ans;
    }
};
