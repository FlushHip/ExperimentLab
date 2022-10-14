#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    std::cout << sol->checkRecord(1) << std::endl;
    std::cout << sol->checkRecord(2) << std::endl;
    std::cout << sol->checkRecord(10101) << std::endl;
    return 0;
}
