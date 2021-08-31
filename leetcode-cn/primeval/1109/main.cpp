#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    std::vector<std::vector<int>> A{
        { 1, 2, 10 },
        { 2, 3, 20 },
        { 2, 5, 25 },
    };
    std::vector<std::vector<int>> B{
        { 1, 2, 10 },
        { 2, 2, 15 },
    };
    std::vector<std::vector<int>> C{
        { 1, 5, 10 },
    };

    std::cout << sol->corpFlightBookings(A, 5) << std::endl;
    std::cout << sol->corpFlightBookings(B, 2) << std::endl;
    std::cout << sol->corpFlightBookings(C, 10) << std::endl;

    return 0;
}
