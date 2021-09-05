// TAG : k进制
class Solution {
public:
    int rand10() {
        int n = 0;
        do {
            n = ((rand7() - 1) * 7) + rand7() - 1;
        } while (n >= 40);
        return n % 10 + 1;
    }
};
