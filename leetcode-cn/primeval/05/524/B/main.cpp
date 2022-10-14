#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    std::pair<std::string, std::vector<std::string>> v[EN]{
        { "abpcplea", { "ale","apple","monkey","plea" } },
        { "abpcplea", { "a","b","c" } },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->findLongestWord(v[L].first, v[L].second);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
