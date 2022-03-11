class Solution {
public:
    int countHighestScoreNodes(vector<int>& parents) {
        int n = (int)parents.size();
        std::vector<std::pair<std::vector<int>, int>> trees(n, { {}, 0 });
        for (int i = 1; i < n; ++i) {
            trees[parents[i]].first.push_back(i);
        }
        std::stack<std::pair<int, std::size_t>> st;
        int p = 0; do {
            if (trees[p].first.empty()) {
                trees[p].second = 1;
                auto [root, index] = st.top();
                st.pop();
                if (index != trees[root].first.size()) {
                    st.emplace(root, index + 1);
                    p = trees[root].first[index];
                } else {
                    trees[root].second = 1;
                    for (const auto cld : trees[root].first) {
                        trees[root].second += trees[cld].second;
                    }
                }
            } else {
                st.emplace(p, 1);
                p = trees[p].first[0];
            }
        } while (!st.empty());

        std::map<unsigned long long, int> ans;
        for (int i = 0; i < n; ++i) {
            unsigned long long score = 1ull;
            if (i) {
                score *= (n - trees[i].second);
            }
            for (auto cld : trees[i].first) {
                score *= trees[cld].second;
            }
            ++ans[score];
        }
        return ans.rbegin()->second;
    }
};
