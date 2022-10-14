class Solution {
public:
    int getSum(int a, int b) {
        for (int sum = 0, fo = 0; b; ) {
            sum = a ^ b;
            fo = (unsigned int)(a & b) << 1;
            a = sum;
            b = fo;
        }
        return a;
    }
};
