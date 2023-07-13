#include "headers.h"

class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        std::vector<double> d_cards(cards.begin(), cards.end());
        return dfs(d_cards);
    }

private:
    static int lowbit(int x) { return x & -x; }

    static int bit_cnt(int x) {
        int ret = 0;
        for (; x; x -= lowbit(x)) {
            ++ret;
        }
        return ret;
    }

    static constexpr double eps = 1e-6;

    bool dfs(std::vector<double> cards) {
        int n = static_cast<int>(cards.size());
        if (n == 1) {
            return std::fabs(cards.front() - 24) < eps;
        }
        for (int origin = (1 << n) - 1, bits = origin; bits > 0;
             bits = (bits - 1) & origin) {
            if (bit_cnt(bits) == 2) {
                std::vector<double> n_cards;
                std::vector<double> candidates;
                for (int i = 0; i < n; ++i) {
                    if (1 << i & bits) {
                        candidates.push_back(cards[i]);
                    } else {
                        n_cards.push_back(cards[i]);
                    }
                }
                n_cards.push_back({});
                // +
                n_cards.back() = candidates.front() + candidates.back();
                if (dfs(n_cards)) {
                    return true;
                }
                // *
                n_cards.back() = candidates.front() * candidates.back();
                if (dfs(n_cards)) {
                    return true;
                }
                // -
                n_cards.back() = candidates.front() - candidates.back();
                if (dfs(n_cards)) {
                    return true;
                }
                n_cards.back() = -n_cards.back();
                if (dfs(n_cards)) {
                    return true;
                }
                // /
                if (std::fabs(candidates.back()) >= eps) {
                    n_cards.back() = candidates.front() / candidates.back();
                    if (dfs(n_cards)) {
                        return true;
                    }
                }
                if (std::fabs(candidates.front()) >= eps) {
                    n_cards.back() = candidates.back() / candidates.front();
                    if (dfs(n_cards)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
