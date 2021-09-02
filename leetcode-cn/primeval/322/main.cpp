#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 5;

    auto sol = std::make_unique<Solution>();

    std::pair<int, std::vector<int>> pr[EN]{
        { 11, { 1, 2, 5 } },
        { 3, { 2 } },
        { 0, { 1 } },
        { 1, { 1 } },
        { 2, { 1 } },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        int ans = sol->coinChange(pr[L].second, pr[L].first);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
