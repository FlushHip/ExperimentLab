class Solution {
public:
    int reverse(int x) {
        auto ans = std::to_string(x);
        if (ans.front() == '-') {
            for (auto it = std::next(ans.begin()); it != ans.end(); ++it) {
                std::iter_swap(it, std::prev(it));
            }
        }
        std::reverse(ans.begin(), ans.end());

        int res = 0;
        try {
            res = std::stoi(ans);
        } catch (const std::out_of_range &) {
        }
        return res;
    }
};
