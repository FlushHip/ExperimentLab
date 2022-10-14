class Solution {
public:
    int minimumLength(string s) {
        int n = (int)s.size();
        int l = 0, r = n - 1;
        for (; l < r && s[l] == s[r]; ) {
            for (; l < r && s[l] == s[r]; ++l) {}
            for (int t = s[r]; l <= r && t == s[r]; --r) {}
        }

        return r - l + 1;
    }
};
