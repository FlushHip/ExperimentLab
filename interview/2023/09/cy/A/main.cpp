#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> matrix[i][j];
            }
        }
        dbg(matrix);
        for (int i = 0; i < n / 2; ++i) {
            for (int j = i; j < n - 1 - i; ++j) {
                int t = matrix[i][j];
                matrix[i][j] = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
                matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
                matrix[j][n - 1 - i] = t;
            }
        }
        dbg(matrix);

        std::cout << std::endl;
    }
    return 0;
}
