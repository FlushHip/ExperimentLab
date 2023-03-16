#include <iostream>
#include <array>

int main(int argc, char **argv)
{
    std::array<std::array<int, 3>, 2> a;
    std::array<std::array<int, 2>, 3> b;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cin >> b[i][j];
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            int ans = 0;
            for (int k = 0; k < 3; ++k) {
                ans += a[i][k] * b[k][j];
            }
            std::cout << ans << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}