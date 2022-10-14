#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    std::pair<int, std::vector<int>> v[EN]{
        { 9, { -1, 0, 3, 5, 9, 12 } },
        { 2, { -1, 0, 3, 5, 9, 12 } },
    };

    auto sol = std::make_unique<Solution>();

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->search(v[L].second, v[L].first);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
