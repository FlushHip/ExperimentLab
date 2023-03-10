#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    VList<> v{0};

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto sol = std::make_unique<MinStack>();
        std::vector<int> ans;
        sol->push(-2);
        sol->push(0);
        sol->push(-3);
        ans.push_back(sol->getMin());
        sol->pop();
        ans.push_back(sol->top());
        ans.push_back(sol->getMin());

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
