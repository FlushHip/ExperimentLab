#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    VList<std::vector<int>> v{
        {100, 80, 60, 70, 60, 75, 85},
        {1, 2, 3, 4, 5, 0},
        {2, 1, 2, 3, 4, 5, 0},
        {5, 4, 3, 2, 1, 6},
        {100},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto sol = std::make_unique<StockSpanner>();
        std::vector<int> ans(v[L].size());
        std::generate(ans.begin(), ans.end(),
            [sol = std::move(sol), it = v[L].begin()]() mutable {
                return sol->next(*it++);
            });

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::steady_clock::now() - start_epoch) * 1000);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m" << std::boolalpha << ans
                  << std::endl
                  << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                  << duration.count() << "ms\x1b[0m" << std::endl
                  << std::endl;
    }

    return 0;
}
