class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        long long tx = 0;
        for (int n = x; n; n /= 10) {
            tx *= 10;
            tx += n % 10;
        }
        return tx == x;
    }
};
