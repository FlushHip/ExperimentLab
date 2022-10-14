#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<char> A { 'a' };
    std::vector<char> B { 'a', 'a', 'b', 'b', 'c', 'c', 'c' };
    std::vector<char> C { 'a','b','b','b','b','b','b','b','b','b','b','b','b' };

    std::cout << sol.compress(A) << std::endl;
    std::cout << sol.compress(B) << std::endl;
    std::cout << sol.compress(C) << std::endl;
    return 0;
}
