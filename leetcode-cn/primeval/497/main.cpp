#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    std::vector<std::vector<int>> rects[EN]{
        {
            { 1, 1, 5, 5 },
        },
        {
            { -2, -2, -1, -1 },
            { 1, 0, 3, 0 }
        },
    };

    std::unique_ptr<Solution> sol[EN];
    for (int i = 0; i < EN; ++i) {
        sol[i] = std::make_unique<Solution>(rects[i]);
    }

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;
        std::vector<std::vector<int>> ans;
        for (int i = 0; i < 10; ++i) {
            ans.emplace_back(sol[L]->pick());
        }
        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
