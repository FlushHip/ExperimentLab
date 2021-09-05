// TAG : k进制
class Solution {
public:
    int rand10() {
        for ( ; ; ) {
            int ans = 0;
            for (int i = 0; i < 4; ++i) {
                ans <<= 1;
                ans |= rand2();
            }
            if (ans > 0 && ans < 11) {
                return ans;
            }
        }
        return 0;
    }

    int rand2() {
        int ans = 0;
        while ((ans = rand7()) > 6) {}
        return ans % 2;
    }
};
