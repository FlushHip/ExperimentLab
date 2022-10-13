class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        if (!arr.size()) {
            return 0;
        }

        int beginSum = arr[0], ans = 0, n = (int)arr.size();
        for (int L = 1; L <= n; L += 2) {
            int sum = beginSum;
            ans += sum;
            for (int i = 1; i + L <= n; ++i) {
                sum = sum - arr[i - 1] + arr[i + L - 1];
                ans += sum;
            }
            if (L + 2 <= n) {
                beginSum += arr[L] + arr[L + 1];
            }
        }

        return ans;
    }
};
