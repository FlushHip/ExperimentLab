#include <iostream>
#include <array>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n && n; ) {
        std::array<int, 100 + 1> scores = { 0 };
        for (int x; n--; ) {
            std::cin >> x;
            ++scores[x];
        }
        std::cin >> n;
        std::cout << scores[n] << std::endl;
    }
    return 0;
}