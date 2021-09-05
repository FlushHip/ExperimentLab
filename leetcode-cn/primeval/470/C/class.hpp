// TAG : k进制
class Solution {
public:
    int rand10() {
        for (; ;) {
            int n = ((rand7() - 1) * 7) + rand7() - 1;
            if (n < 40) {
                return n % 10 + 1;
            }
            n = (n - 40) * 7 + rand7() - 1;
            if (n < 60) {
                return n % 10 + 1;
            }
            n = (n - 60) * 7 + rand7() - 1;
            if (n < 20) {
                return n % 10 + 1;
            }
        }

        return 0;
    }
};
