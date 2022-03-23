class Solution {
public:
    bool isMatch(string s, string p) {
        std::regex reg(p);
        return std::regex_match(s, reg);
    }
};
