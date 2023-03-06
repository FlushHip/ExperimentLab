#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    VList<> v{
        1,
        2,
        3,
        4,
        5,
        10,
    };

    auto printH = [] { std::cout << 'H'; };
    auto printO = [] { std::cout << 'O'; };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        for (int i = 0; i < v[L]; ++i) {
            auto sol = std::make_unique<H2O>();
            std::thread t1([&] { sol->hydrogen(printH); });
            std::thread t2([&] { sol->hydrogen(printH); });
            std::thread t3([&] { sol->oxygen(printO); });
            t1.join();
            t2.join();
            t3.join();
        }
        std::cout << std::endl;

        int ans = 0;

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
