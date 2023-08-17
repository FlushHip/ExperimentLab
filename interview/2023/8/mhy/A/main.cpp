#include <iostream>

int main() {
    for (int n{}, m{}; std::cin >> n >> m;) {
        struct point_t {
            int x{}, y{};
        };
        point_t a, b, c;
        std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        int d_1_x = std::abs(b.x - a.x), d_1_y = std::abs(b.y - a.y);
        int d_2_x = std::abs(c.x - b.x), d_2_y = std::abs(c.y - b.y);
        int ans = std::min(d_1_x, n - d_1_x) + std::min(d_1_y, m - d_1_y);
        ans += std::min(d_2_x, n - d_2_x) + std::min(d_2_y, m - d_2_y);
        std::cout << ans << std::endl;
    }
    return 0;
}
