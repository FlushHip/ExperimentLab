#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 1;

    auto sol = std::make_unique<Solution>();

    std::pair<int, std::vector<int>> arr[EN]{
        { 4, { 1, 3, 5, 7, 2, 4, 6, 8 } },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->smallestK(arr[L].second, arr[L].first);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
