#include <iostream>
#include <queue>
#include <vector>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i)
            std::cin >> data[i];
        std::priority_queue<int, std::vector<int>, std::greater<int>> que(data.begin(), data.end());
        int ans = 0;
        while (que.size() > 1) {
            int a = que.top();
            que.pop();
            int b = que.top();
            que.pop();
            ans += a + b;
            que.emplace(a + b);
        }
        std::cout << ans << std::endl;
    }
    return 0;
}