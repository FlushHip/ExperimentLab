class Solution {
    inline int get_cnt(int num, int n)
    {
        int64_t ans = 0;
        for (int64_t lhs = num, rhs = num; lhs <= n; lhs = lhs * 10, rhs = rhs * 10 + 9) {
            ans += std::min(static_cast<int64_t>(n), rhs) - lhs + 1;
        }
        return static_cast<int>(ans);
    };


public:
    int findKthNumber(int n, int k) {
        int ans = 1;
        while (k != 1) {
            int cnt = get_cnt(ans, n);
            if (k > cnt) {
                k -= cnt;
                ++ans;
            } else {
                ans *= 10;
                --k;
            }
        }
        return ans;
    }
};
