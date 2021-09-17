#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    std::pair<std::vector<std::string>, std::vector<std::vector<char>>> v[EN]{
        { { "oath","pea","eat","rain" }, {
                { 'o', 'a', 'a', 'n' },
                { 'e', 't', 'a', 'e' },
                { 'i', 'h', 'k', 'r' },
                { 'i', 'f', 'l', 'v' },
        }},
        { { "abcd" }, {
                { 'a', 'b' },
                { 'c', 'd' },
        }},
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->findWords(v[L].second, v[L].first);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
