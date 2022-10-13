#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::vector<std::vector<int>> graphA {
        { 1, 2 },
        { 3 },
        { 3 },
        {  },
    };
    std::vector<std::vector<int>> graphB {
        { 4, 3, 1 },
        { 3, 2, 4 },
        { 3 },
        { 4 },
        {  },
    };
    std::vector<std::vector<int>> graphC {
        { 1 },
        {  },
    };
    std::vector<std::vector<int>> graphD {
        { 1, 2, 3 },
        { 2 },
        { 3 },
        {  },
    };
    std::vector<std::vector<int>> graphE {
        { 1, 3 },
        { 2 },
        { 3 },
        {  },
    };

    std::cout << sol.allPathsSourceTarget(graphA) << std::endl;
    std::cout << sol.allPathsSourceTarget(graphB) << std::endl;
    std::cout << sol.allPathsSourceTarget(graphC) << std::endl;
    std::cout << sol.allPathsSourceTarget(graphD) << std::endl;
    std::cout << sol.allPathsSourceTarget(graphE) << std::endl;
    return 0;
}
