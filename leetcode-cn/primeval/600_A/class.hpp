class Solution {
public:
    int findIntegers(int n) {
        static const int SIZE = 32;

        std::vector<int> dp(SIZE, 1);
        dp[1] = 2;
        for (int i = 2; i < SIZE; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        int last = 0, ans = 0;
        std::bitset<SIZE> N(n);
        for (int i = 0; i < SIZE; ++i) {
            int L = SIZE - i - 1;
            int current = N.test(L);
            if (current) {
                ans += dp[L];
                if (last) {
                    --ans;
                    break;
                }
            }
            last = current;
        }

        return ans + 1;
    }
};
