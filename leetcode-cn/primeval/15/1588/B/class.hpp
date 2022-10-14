class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = (int)arr.size(), ans = 0;
        for (int i = 0; i < n; ++i) {
            int lhs_num = i, rhs_num = n - i - 1;
            int lhs_odd = (lhs_num + 1) / 2
                , lhs_even = lhs_num / 2 + 1;
            int rhs_odd = (rhs_num + 1) / 2
                , rhs_even = rhs_num / 2 + 1;
            ans += arr[i] * (lhs_odd * rhs_odd + lhs_even * rhs_even);
        }

        return ans;
    }
};
