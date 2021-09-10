#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    std::pair<int, std::vector<int>> v[EN]{
        { 22, { 5, 1, 5 } },
        { 25, { 3, 4, 1, 2 } },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->chalkReplacer(v[L].second, v[L].first);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
