class Solution {
public:
    vector<string> cellsInRange(string s) {
        std::vector<std::string> ans;
        std::string tmp(2, 0);
        int r_l = s[1], r_r = s[4], c_l = s[0], c_r = s[3];
        for (int c = c_l; c <= c_r; ++c) {
            for (int r = r_l; r <= r_r; ++r) {
                tmp[0] = c, tmp[1] = r;
                ans.emplace_back(tmp);
            }
        }
        return ans;
    }
};
