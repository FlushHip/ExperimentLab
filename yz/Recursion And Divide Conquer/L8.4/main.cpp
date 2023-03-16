#include <iostream>

int get_childs_number(int m, int n)
{
    if (m > n)
        return 0;
    return 1 + get_childs_number(m * 2, n)
        + get_childs_number(m * 2 + 1, n);
}

int main(int argc, char **argv)
{
    for (int m, n; std::cin >> m >> n && m + n; ) {
        std::cout << get_childs_number(m, n) << std::endl;
    }
    return 0;
}