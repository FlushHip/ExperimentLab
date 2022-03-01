class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        auto cmp = [](const std::pair<char, int> &lhs, const std::pair<char, int> &rhs)
        {
            return std::less<int>{}(lhs.second, rhs.second);
        };
        std::vector<std::pair<char, int>> vec{
            { 'a', a },
            { 'b', b },
            { 'c', c },
        };
        std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>, decltype(cmp)> que(cmp, std::move(vec));

        std::string ans;
        for (; !que.empty();) {
            auto node = que.top();
            que.pop();
            if (node.second) {
                if (ans.size() < 2u || ans.back() != node.first || *std::next(ans.rbegin()) != node.first) {
                    ans.push_back(node.first);
                    --node.second;
                    que.push(node);
                } else if (!que.empty()) {
                    auto node2 = que.top();
                    que.pop();
                    if (node2.second) {
                        ans.push_back(node2.first);
                        --node2.second;
                        que.push(node2);
                    }
                    que.push(node);
                }
            }
        }

        return ans;
    }
};
