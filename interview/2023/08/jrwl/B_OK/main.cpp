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
            auto search = [&line](int a, int b) {
                return *std::min_element(line.begin() + a, line.begin() + b);
            };
            auto modify = [&line](int a, int b, int c) {
                for (int i = a; i < b; ++i) {
                    line[i] += c;
                }
            };
            switch (op.back()) {
            case 'Q':
                std::cout << search(a, b) << std::endl;
                break;
            case 'B': {
                auto res = search(a, b);
                if (res >= c) {
                    std::cout << "OK!" << std::endl;

                    modify(a, b, -c);
                    ump[{a, b}] += c;
                } else {
                    std::cout << "Fail!" << std::endl;
                }
            } break;
            case 'R': {
                auto res = n - search(a, b);
                if (c > res) {
                    std::cout << "Fail!" << std::endl;
                    break;
                }
                if (ump[{a, b}] >= c) {
                    std::cout << "OK!" << std::endl;

                    modify(a, b, c);
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
