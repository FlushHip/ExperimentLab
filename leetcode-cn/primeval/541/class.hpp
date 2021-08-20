class Solution {
public:
    string reverseStr(string s, int k) {
        for (int index = 0, n = s.size(); index < n; index += (k << 1)) {
            if (n - index > k) {
                std::reverse(s.begin() + index, s.begin() + index + k);
            } else {
                std::reverse(s.begin() + index, s.end());
                break;
            }
        }
        return s;
    }
};
