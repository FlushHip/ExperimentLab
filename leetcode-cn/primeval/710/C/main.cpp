#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 6;

    std::pair<int, std::vector<int>> v[EN]{
        { 1, {  } },
        { 2, {  } },
        { 3, { 1 } },
        { 4, { 2 } },
        { 4, { 0, 1, 2 } },
        { 4, { 10, 11, 12 } },
    };

    std::unique_ptr<Solution> sol[EN];
    for (int i = 0; i < EN; ++i) {
        sol[i] = std::make_unique<Solution>(v[i].first, v[i].second);
    }

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        std::vector<int> ans;
        for (int i = 0; i < 10; ++i) {
            ans.push_back(sol[L]->pick());
        }

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
