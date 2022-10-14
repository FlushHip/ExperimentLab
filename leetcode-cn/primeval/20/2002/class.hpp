class Solution {
    enum { MAX_BITS = 12 };
public:
    int maxProduct(string s) {
        int n = (int)s.size();
        int ans = 0;
        for (int i = 1; i < (1 << n); ++i) {
            std::bitset<MAX_BITS> bits(i);
            std::string line, res;
            for (int i = 0; i < n; ++i) {
                if (bits.test(i)) {
                    line.push_back(s[i]);
                } else {
                    res.push_back(s[i]);
                }
            }
            if (!std::equal(line.begin(), line.end()
                , line.rbegin(), line.rend())) {
                    continue;
            }

            int m = (int)res.size();
            for (int j = 1; j < (1 << m); ++j) {
                std::bitset<MAX_BITS> bits(j);
                std::string line2;
                for (int j = 0; j < m; ++j) {
                    if (bits.test(j)) {
                        line2.push_back(res[j]);
                    }
                }
                if (!std::equal(line2.begin(), line2.end()
                    , line2.rbegin(), line2.rend())) {
                        continue;
                }

                ans = std::max(ans, (int)(line.size() * line2.size()));
            }
        }
        return ans;
    }
};
