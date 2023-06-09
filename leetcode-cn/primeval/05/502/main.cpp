#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    std::tuple<int, int, std::vector<int>, std::vector<int>> tp[EN]{
        {2, 0, {1, 2, 3}, {0, 1, 1}},
        {3, 0, {1, 2, 3}, {0, 1, 2}},
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->findMaximizedCapital(std::get<0>(tp[L]),
            std::get<1>(tp[L]), std::get<2>(tp[L]), std::get<3>(tp[L]));

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
