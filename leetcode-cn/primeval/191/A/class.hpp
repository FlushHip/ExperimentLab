class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        for (; n; ++ans) {
            n -= (n & (-n));
        }
        return ans;
    }
};
