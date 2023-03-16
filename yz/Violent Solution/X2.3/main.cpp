#include <iostream>

int main(int argc, char **argv)
{
    for (int n, x, y, z; std::cin >> n >> x >> y >> z; ) {
        for (int q = 9; q > 0; q--) {
            for (int h = 9; h >= 0; h--) {
                int price = q * 10000 + x * 1000 + y * 100 + z * 10 + h;
                if (price / n * n == price) {
                    std::cout << q << " " << h << " " << price / n << std::endl;
                    goto EXIT;
                }
            }
        }
        std::cout << 0 << std::endl;
        EXIT:;
    }
    return 0;
}