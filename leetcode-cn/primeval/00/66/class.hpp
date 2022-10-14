class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        std::vector<int> ans(digits.rbegin(), digits.rend());
        int carry = 0;
        ++ans[0];
        for (auto &n : ans) {
            if (carry) {
                n += carry;
            }
            if (carry = n / 10; !carry) {
                break;
            }
            n %= 10;
        }
        if (carry) {
            ans.push_back(carry);
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
