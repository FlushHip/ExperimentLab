class Solution {
public:
    bool hasAlternatingBits(int n) {
        unsigned int N = n;
        return (((N ^ (N >> 1)) + 1) & (N ^ (N >> 1))) == 0;
    }
};
