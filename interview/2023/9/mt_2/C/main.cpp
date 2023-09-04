#include <array>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (std::string line; std::cin >> line;) {
        int n = static_cast<int>(line.size());
        std::vector<std::array<int, 2>> f(n, {0, 0});
        f[0][0] = line[0] == '1';
        f[0][1] = line[0] == '0';
        for (int i = 1; i < n; ++i) {
            int cnt = 0;
            if (line[i] == '0') {
                f[i][0] = f[i - 1][1];
                f[i][1] = 1 + f[i - 1][0];
            } else {
                f[i][0] = 1 + f[i - 1][1];
                f[i][1] = f[i - 1][0];
            }
        }
        dbg(f);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1, end_0 = 0, end_1 = 1; j >= 0; --j) {
                ans += std::min(f[i][0] - (j > 0 ? f[j - 1][end_0] : 0),
                    f[i][1] - (j > 0 ? f[j - 1][end_1] : 0));
                end_0 = 1 - end_0;
                end_1 = 1 - end_1;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
