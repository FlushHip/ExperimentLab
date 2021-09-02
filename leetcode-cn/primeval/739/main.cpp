#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 3;

    auto sol = std::make_unique<Solution>();

    std::vector<int> temperatures[EN]{
        { 73, 74, 75, 71, 69, 72, 76, 73 },
        { 30, 40, 50, 60 },
        { 30, 60, 90 },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->dailyTemperatures(temperatures[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
