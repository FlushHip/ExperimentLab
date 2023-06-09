#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    std::pair<int, int> xy[EN]{
        {1, 4},
        {3, 1},
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->hammingDistance(xy[L].first, xy[L].second);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
