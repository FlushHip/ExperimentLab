class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = (int)s.size();
        std::vector<int> dp_r(n), dp_l(n);
        std::vector<int> sum(n, s.front() == '*');

        dp_r[0] = s.front() == '|' ? 0 : -1;
        dp_l[n - 1] = s.back() == '|' ? n - 1 : n;
        for (int i = 1; i < n; ++i) {
            dp_r[i] = s[i] == '|' ? i : dp_r[i - 1];
            dp_l[n - i - 1] = s[n - i - 1] == '|' ? n - i - 1 : dp_l[n - i];
            sum[i] = s[i] == '*' ? sum[i - 1] + 1 : sum[i - 1];
        }

        std::vector<int> ans;
        for (const auto & querie : queries) {
            int lhs = querie[0], rhs = querie[1];
            if (dp_r[rhs] == -1 || dp_l[lhs] == n || dp_r[rhs] < dp_l[lhs]) {
                ans.push_back(0);
                continue;
            }
            int tmp = sum[dp_r[rhs]] - sum[dp_l[lhs]];
            ans.push_back(tmp);
        }

        return ans;
    }
};
