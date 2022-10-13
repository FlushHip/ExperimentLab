class Solution {
public:
    string convert(string s, int numRows) {
        int n = (int)s.size();
        int numCols = numRows == 1
            ? n
            : (n * 1.0 / (numRows * 2 - 2) + 1) * (numRows - 1);
        std::map<int, char> mp;
        for (int i = 0, y = 0, x = 0, f = 0; i < n; ++i) {
            int num = y * numCols + x;
            mp[num] = s[i];

            if (f == 0) {
                if (++y == numRows) {
                    --y;
                    f = 1;
                }
            }
            if (f == 1) {
                --y;
                ++x;
                if (y <= 0) {
                    y = 0;
                    f = 0;
                }
            }
        }

        std::string ans(s);
        std::transform(mp.begin(), mp.end()
            , ans.begin(), [](const auto &pr) {
            return pr.second;
        });
        return ans;
    }
};
