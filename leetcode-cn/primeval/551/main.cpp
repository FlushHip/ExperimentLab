#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::cout << std::boolalpha << sol.checkRecord("PPALLP") << std::endl;
    std::cout << std::boolalpha << sol.checkRecord("PPALLL") << std::endl;
    return 0;
}
