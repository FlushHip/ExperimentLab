// TAG : 数位DP的记忆化搜
class Solution {
public:
    int findIntegers(int n) {
        std::bitset<32> digits(n);
        std::vector<std::vector<int>> dp(32
            , std::vector<int>(2, std::numeric_limits<int>::max()));
        int index = 31;
        for (; !digits.test(index); --index) {}
        return dfs(digits, dp, index, 0, true);
    }

    int dfs(const std::bitset<32> &digits, std::vector<std::vector<int>> &dp
        , int index, int last, bool limit) {
        if (index < 0) {
            return 1;
        }
        if (!limit && dp[index][last] != std::numeric_limits<int>::max()) {
            return dp[index][last];
        }
        int ans = 0, top = limit ? digits[index] : 1;
        for (int i = 0; i <= top; ++i) {
            if (last == 1 && i == 1) {
                break;
            }
            ans += dfs(digits, dp, index - 1, i, limit && i == top);
        }

        if (!limit) {
            dp[index][last] = ans;
        }

        return ans;
    }

private:
};
