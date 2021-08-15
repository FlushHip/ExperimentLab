class Solution {
public:
    int add(int a, int b) {
        int ans = 0, up = 0;

        do {
            ans = a ^ b;
            up = static_cast<int>(static_cast<unsigned int>(a & b) << 1);
            a = ans;
            b = up;
        } while (up);

        return ans;
    }
};
