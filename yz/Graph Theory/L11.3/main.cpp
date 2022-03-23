#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int find(std::vector<int> &fathers, const int x)
{
    if (fathers[x] == x)
        return x;
    return fathers[x] = find(fathers, fathers[x]);
}

int main(int argc, char **argv)
{
    std::freopen("in.dat", "r", stdin);

    constexpr auto kLen = 10000 + 1;
    for (int k = 1, x, y; std::cin >> x >> y && x + 1 && y + 1; ++k) {
        std::cout << "Case " << k << " is ";
        int n = std::max(x, y);
        if (!n) {
            std::cout << "a tree." << std::endl;
            continue;
        }

        std::vector<int> fathers(kLen);
        std::vector<int> in(kLen, 0);
        std::vector<bool> used(kLen, false);
        std::iota(fathers.begin(), fathers.end(), 0);

        do {
            used[x] = used[y] = true;
            ++in[y];
            int fx = find(fathers, x);
            int fy = find(fathers, y);
            if (fx != fy)
                fathers[fx] = fy;
            n = std::max(n, std::max(x, y));
        } while (std::cin >> x >> y && x + y);

        fathers.resize(n + 1);
        in.resize(n + 1);

        int ans = 0;
        for (int i = 1; i <= n; ++i)
            if (used[i] && find(fathers, i) == i)
                ++ans;
        if (ans != 1) {
            std::cout << "not a tree." << std::endl;
            continue;
        }
        int num[2] = { 0, 0 };
        for (int i = 1; i <= n; ++i) {
            if (used[i] && in[i] < 2)
                ++num[in[i]];
        }
        if (num[0] == 1 && num[1] == std::count(used.begin() + 1, used.end(), true) - 1)
            std::cout << "a tree." << std::endl;
        else
            std::cout << "not a tree." << std::endl;
    }
    return 0;
}