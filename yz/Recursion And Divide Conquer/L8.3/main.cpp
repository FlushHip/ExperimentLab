#include <iostream>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        int f[2] = { 0, 1 };
        for (int i = 2; i <= n; ++i) {
            f[0] += f[1];
            std::swap(f[0], f[1]);
        }
        std::cout << (n > 0 ? f[1] : f[0]) << std::endl;
    }
    return 0;
}