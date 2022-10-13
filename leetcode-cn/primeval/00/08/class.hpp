class Solution {
public:
    int myAtoi(string s) {
        int n = (int)s.size();
        int begin = 0;
        for (; begin < n; ++begin) {
            if (!std::isspace(s[begin])) {
                break;
            }
        }
        if (begin == n) {
            return 0;
        }
        if (!(std::isdigit(s[begin]) || (s[begin] == '-' || s[begin] == '+')
                && begin + 1 < n
                && std::isdigit(s[begin + 1]))) {
            return 0;
        }
        int end = begin + (!std::isdigit(s[begin]) ? 1 : 0);
        for (; end < n; ++end) {
            if (!std::isdigit(s[end])) {
                break;
            }
        }
        int ans = 0;
        try {
            ans = std::stoi(s.substr(begin, end - begin));
        } catch (const std::out_of_range &) {
            ans = s[begin] == '-' ? std::numeric_limits<int>::min()
                : std::numeric_limits<int>::max();
        }
        return ans;
    }
};
