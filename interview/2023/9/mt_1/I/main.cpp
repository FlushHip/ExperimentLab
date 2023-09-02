#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        std::string line;
        std::cin >> line;
        int ans = n;
        for (int x = 1; x <= n; ++x) {
            int y = n / x;
            if (x * y != n) {
                continue;
            }
            int idx = 0;
            std::vector<std::vector<int>> mtx(x, std::vector<int>(y, 0));
            std::function<void(int, int, int)> fn = [&](int i, int j, int idx) {
                mtx[i][j] = idx;
                for (auto&& [dir_x, dir_y] :
                    std::initializer_list<std::pair<int, int>>{
                        {0, 1},
                        {0, -1},
                        {1, 0},
                        {-1, 0},
                    }) {
                    int ii = i + dir_x;
                    int jj = j + dir_y;
                    if (ii >= 0 && ii < x && jj >= 0 && jj < y &&
                        line[i * y + j] == line[ii * y + jj] &&
                        mtx[ii][jj] == 0) {
                        fn(ii, jj, idx);
                    }
                }
            };
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    if (mtx[i][j] == 0) {
                        fn(i, j, ++idx);
                        dbg(x, y, mtx);
                    }
                }
            }
            ans = std::min(ans, idx);
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
