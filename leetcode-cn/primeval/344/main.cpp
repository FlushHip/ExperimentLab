#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<char> A{ 'h', 'e', 'l', 'l', 'o' };
    sol.reverseString(A);

    for (const auto c : A) {
        std::cout << c;
    }
    std::cout << std::endl;
    return 0;
}
