#include <iostream>

int main() {
    for (int n{}; std::cin >> n;) {
        std::string line;
        std::cin >> line;
        int ans = 0;
        for (int i = 1, j = 0; i < n; ++i) {
            if (line[j] == line[i]) {
                ++ans;
            } else {
                j = i;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
