#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::cout << sol.reverseStr("abcdefg", 2) << std::endl;
    std::cout << sol.reverseStr("abcd", 2) << std::endl;
    std::cout << sol.reverseStr("abcd", 3) << std::endl;
    std::cout << sol.reverseStr("abcd", 5) << std::endl;
    std::cout << sol.reverseStr("a", 1) << std::endl;

    return 0;
}
