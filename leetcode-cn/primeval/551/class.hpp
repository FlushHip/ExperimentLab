class Solution {
public:
    bool checkRecord(string s) {
        return std::count(s.begin(), s.end(), 'A') < 2
            && s.find("LLL") == std::string::npos;
    }
};
