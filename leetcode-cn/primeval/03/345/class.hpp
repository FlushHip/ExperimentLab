class Solution {
public:
    string reverseVowels(string s) {
        for (int l = 0, r = (int)s.size() - 1; l < r; ) {
            l = std::find_if(s.begin() + l, s.end()
                , std::bind(&Solution::isvowel, this, std::placeholders::_1))
                - s.begin();
            r = s.size() - (std::find_if(s.rbegin() + (s.size() - r - 1), s.rend()
                , std::bind(&Solution::isvowel, this, std::placeholders::_1))
                - s.rbegin()) - 1;
            if (l >= r) {
                break;
            }
            std::swap(s[l], s[r]);
            ++l;
            --r;
        }

        return s;
    }

    bool isvowel(char c) {
        static const std::string VOWELS = "aeiou";
        char cc = std::tolower(c);
        return std::string::npos != VOWELS.find(cc);
    }
};
