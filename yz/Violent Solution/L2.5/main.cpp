#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    int n;
    char l, w;
    while (std::cin >> n >> l >> w) {
        if ((n + 1) / 2 % 2)
            std::swap(l, w);
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                if ((x == 0 && y == 0) || (x == 0 && y + 1 == n)
                    || (x + 1 == n && y == 0) || (x + 1 == n && y + 1 == n)) {
                    std::cout << ' ';
                    continue;
                }
                int t = 0;
                if ((y - x >= 0 && y + x - n + 1 <= 0) ||
                    (y - x <= 0 && y + x - n + 1 >= 0))
                    t = x;
                else t = y;
                std::cout << (t % 2 ? l : w);
            }
            std::cout << std::endl << std::endl;
        }
    }
    return 0;
}