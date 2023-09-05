#include <iostream>
#include <vector>

int main() {
    for (int n{}, m{}; std::cin >> n >> m;) {
        bool has_ans = false;
        std::vector<bool> line(n, false);
        int res = n, only = -1;
        for (int L = 0; L < m; ++L) {
            int t{}, x{};
            std::cin >> t >> x;
            --x;
            if (has_ans) {
                continue;
            }
            if (t == 1) {
                if (only == -1) {
                    if (!line[x]) {
                        --res;
                        line[x] = true;
                    }
                    if (res == 0) {
                        has_ans = true;
                        std::cout << L + 1 << std::endl;
                    }
                } else if (only == x) {
                    has_ans = true;
                    std::cout << L + 1 << std::endl;
                }
            } else {
                if (only == -1) {
                    if (!line[x]) {
                        only = x;
                        res = 1;
                    } else {
                        has_ans = true;
                        std::cout << L + 1 << std::endl;
                    }
                } else if (only == x) {
                    continue;
                } else {
                    has_ans = true;
                    std::cout << L + 1 << std::endl;
                }
            }
        }
        if (!has_ans) {
            std::cout << -1 << std::endl;
        }
    }
    return 0;
}
