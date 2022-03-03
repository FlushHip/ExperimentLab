class Solution {
public:
    bool isUgly(int n) {
        if (n <= 0) {
            return false;
        }
        for (const auto i : { 2, 3, 5 }) {
            for (; n % i == 0; n /= i) {}
        }
        return n == 1;
    }
};
