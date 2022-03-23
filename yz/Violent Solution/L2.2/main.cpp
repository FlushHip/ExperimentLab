#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char **argv)
{
    for (int N = 1000; N < 10000 && N * 9 < 10000; ++N) {
        std::string origin = std::to_string(N);
        std::string pre = std::to_string(N * 9);
        std::reverse(origin.begin(), origin.end());
        if (pre == origin)
            std::cout << N << std::endl;
    }
    return 0;
}