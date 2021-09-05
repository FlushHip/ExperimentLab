class Solution {
public:
    int fib(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        int f1 = 0, f2 = 1, ret;
        for (int i = 2; i <= n; i++)
            ret = (f1 + f2) % mod, f1 = f2, f2 = ret;
        return ret;
    }
private:
    const int mod = 1e9 + 7;
};
