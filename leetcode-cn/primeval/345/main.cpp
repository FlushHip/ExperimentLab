#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::cout << sol.reverseVowels("hello") << std::endl;
    std::cout << sol.reverseVowels("") << std::endl;
    std::cout << sol.reverseVowels("leetcode") << std::endl;
    std::cout << sol.reverseVowels("l") << std::endl;
    std::cout << sol.reverseVowels("e") << std::endl;
    std::cout << sol.reverseVowels("le") << std::endl;
    std::cout << sol.reverseVowels("el") << std::endl;
    std::cout << sol.reverseVowels("lel") << std::endl;
    std::cout << sol.reverseVowels("au") << std::endl;
    return 0;
}
