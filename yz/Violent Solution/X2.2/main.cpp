#include <iostream>
#include <algorithm>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        for (int x = 0; x < n / 5 + 1 && x <= 100; ++x) {
            for (int y = 0; y < n / 3 + 1 && y <= 100; ++y) {
                int z = 100 - x - y;
                if (z < 0 || z / 3.0 > n - x * 5 - y * 3)
                    continue;
                std::cout << "x=" << x << ",y=" << y << ",z=" << z << std::endl;
            }
        }
    }
    return 0;
}