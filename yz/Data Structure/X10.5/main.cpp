#include <iostream>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::string i1, i2;
        std::string ans1("23:59:60"), ans2("00:00:00");
        for (std::string a, b, c; n--; ) {
            std::cin >> a >> b >> c;
            if (ans1 > b) {
                ans1 = b;
                i1 = a;
            }
            if (ans2 <= c) {
                ans2 = c;
                i2 = a;
            }
        }
        std::cout << i1 << " " << i2;
    }
    return 0;
}