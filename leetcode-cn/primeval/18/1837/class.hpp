class Solution {
    enum { MAX_LEN = 20 };
public:
    int sumBase(int n, int k) {
        std::array<char, MAX_LEN> str{ 0 };
        std::to_chars(str.data(), str.data() + MAX_LEN, n, k);
        return std::accumulate(str.data(), str.data() + MAX_LEN, 0, [](auto ans, auto c)
        {
            return ans + (c ? c - '0' : 0);
        });
    }
};
