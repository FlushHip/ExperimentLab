#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}, m{}, q{}; std::cin >> m >> n >> q;) {
        std::vector<int> line(m - 1, n);
        std::map<std::pair<int, int>, int> ump;
        for (int L = 0; L < q; ++L) {
            std::string op;
            int a{}, b{}, c{};
            std::cin >> op >> a >> b;
            if (op.back() != 'Q') {
                std::cin >> c;
            }
            dbg(a, b, c, line);
            auto search = [&](int a, int b) {
                return *std::min_element(line.begin() + a, line.begin() + b);
            };
            switch (op.back()) {
            case 'Q':
                std::cout << search(a, b) << std::endl;
                break;
            case 'B': {
                auto res = search(a, b);
                if (res >= c) {
                    std::cout << "OK!" << std::endl;
                    for (int i = a; i < b; ++i) {
                        line[i] -= c;
                    }
                    ump[{a, b}] += c;
                } else {
                    std::cout << "Fail!" << std::endl;
                }
            } break;
            case 'R': {
                /*
                auto sale =
                    n - *std::max_element(line.begin() + a, line.begin() + b);
                if (sale >= c) {
                    std::cout << "OK!" << std::endl;
                    for (int i = a; i < b; ++i) {
                        line[i] += c;
                    }
                } else {
                    std::cout << "Fail!" << std::endl;
                }
                */
                if (ump[{a, b}] >= c) {
                    std::cout << "OK!" << std::endl;
                    for (int i = a; i < b; ++i) {
                        line[i] += c;
                    }
                    ump[{a, b}] -= c;
                } else {
                    std::cout << "Fail!" << std::endl;
                }
            } break;
            }
        }
    }
    return 0;
}
