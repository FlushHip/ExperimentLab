#include <iostream>
#include <vector>
#include <numeric>

int find(std::vector<int> &fathers, const int x)
{
    if (fathers[x] == x)
        return x;
    return fathers[x] = find(fathers, fathers[x]);
}

int main(int argc, char **argv)
{
    for (int n, m; std::cin >> n && n; ) {
        std::cin >> m;
        std::vector<int> fathers(n + 1);
        std::iota(fathers.begin(), fathers.end(), 0);

        for (int i = 0; i < m; ++i) {
            int x, y;
            std::cin >> x >> y;
            int fx = find(fathers, x);
            int fy = find(fathers, y);
            if (fx != fy)
                fathers[fx] = fy;
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i)
            if (find(fathers, i) == i)
                ++ans;
        std::cout << ans - 1 << std::endl;
    }
    return 0;
}