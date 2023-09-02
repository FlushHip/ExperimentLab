#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <unordered_set>
#include <vector>

int main() {
    for (int n{}, m{}; std::cin >> n >> m;) {
        std::vector<std::string> matrix(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> matrix[i];
        }
        auto fn = [&matrix](int i, int j) {
            std::unordered_set<char> ust;
            for (int ii = i; ii < i + 3; ++ii) {
                for (int jj = j; jj < j + 3; ++jj) {
                    ust.insert(matrix[ii][jj]);
                    for (auto [dir_x, dir_y] :
                        std::initializer_list<std::pair<int, int>>{
                            {1, 0},
                            {-1, 0},
                            {0, 1},
                            {0, -1},
                        }) {
                        int x = ii + dir_x;
                        int y = jj + dir_y;
                        if (x >= i && x < i + 3 && y >= j && y < j + 3 &&
                            matrix[x][y] == matrix[ii][jj]) {
                            return false;
                        }
                    }
                }
            }
            return ust.size() == 3 &&
                std::all_of(ust.begin(), ust.end(),
                    [](char c) { return 'A' <= c && c <= 'C'; });
        };
        int ans = 0;
        for (int i = 0; i + 2 < n; ++i) {
            for (int j = 0; j + 2 < m; ++j) {
                ans += fn(i, j);
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
