#include <headers.h>

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    // std::cout << Solution::longestValidParentheses(nullptr, ")()())") << std::endl;
    std::cout << sol.longestValidParentheses(")()())") << std::endl;
    return 0;
}
