#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
    auto get_sum = [](int n) -> int
    {
        int ans = 0;
        for (int i = 1; i < n; ++i)
            if (n % i == 0)
                ans += i;
        return ans;
    };
    std::cout << "E:";
    for (int i = 2; i <= 60; ++i)
        if (i == get_sum(i))
            std::cout << " " << i;
    std::cout << std::endl << "G:";
    for (int i = 2; i <= 60; ++i)
        if (i < get_sum(i))
            std::cout << " " << i;
    std::cout << std::endl;
    return 0;
}