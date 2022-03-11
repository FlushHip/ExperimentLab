class Solution {
public:
    vector<int> addToArrayForm(vector<int>& num, int k) {
        std::vector<int> ans(num.rbegin(), num.rend());
        int carry = 0;
        ans[0] += k;
        for (auto &n : ans) {
            if (carry) {
                n += carry;
            }
            if (carry = n / 10; !carry) {
                break;
            }
            n %= 10;
        }
        for (; carry; carry /= 10) {
            ans.push_back(carry % 10);
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
