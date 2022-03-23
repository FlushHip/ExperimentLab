#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str; ) {
        int n = (int)str.size(), w = 0, h = 0;
        for (w = 3; w <= n; ++w) {
            h = (n + 2 - w) / 2;
            if ((n + 2 - w) % 2 == 0 && h <= w)
                break;
        }

        int pre = 0, next = n - 1;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (j == 0 || i + 1 == h)
                    std::cout << str[pre++];
                else if (j + 1 == w)
                    std::cout << str[next--];
                else
                    std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }
    return 0;
}