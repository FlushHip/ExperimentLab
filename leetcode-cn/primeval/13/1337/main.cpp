#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    std::vector<std::vector<int>> A = {
        {1,1,0,0,0},
        {1,1,1,1,0},
        {1,0,0,0,0},
        {1,1,0,0,0},
        {1,1,1,1,1},
    };
    std::vector<std::vector<int>> B = {
        {1,0,0,0},
        {1,1,1,1},
        {1,0,0,0},
        {1,0,0,0},
    };

    std::cout << sol->kWeakestRows(A, 3) << std::endl;
    std::cout << sol->kWeakestRows(B, 2) << std::endl;

    return 0;
}
