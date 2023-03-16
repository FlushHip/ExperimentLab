#include <iostream>

int main(int argc, char **argv)
{
    for (long long x, y, k; std::cin >> x >> y >> k; ) {
        long long ans = 1ll;
        while (y) {
            if (y % 2)
                ans = (ans % (k - 1)) * (x % (k - 1)) % (k - 1);
            x %= (k - 1);
            x = x * x % (k - 1);
            y /= 2;
        }
        std::cout << (ans ? ans : k - 1) << std::endl;
    }
    return 0;
}