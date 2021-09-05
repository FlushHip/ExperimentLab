// TAG : k进制
class Solution {
public:
    int rand10() {
        int i = 0, j = 0;
        while ((i = rand7()) > 6) {}
        while ((j = rand7()) > 5) {}
        return i % 2 ? j : j + 5;
    }
};
