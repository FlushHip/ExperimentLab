class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        auto v = { 2, 3, 5, 7, 11, 13, 17, 19 };
        int ans = 0;
        for (int i = left; i <= right; ++i) {
            int sum = 0;
            for (int L = i; L; L &= L - 1) {
                ++sum;
            }
            ans += (int)std::binary_search(v.begin(), v.end(), sum);
        }
        return ans;
    }
};
