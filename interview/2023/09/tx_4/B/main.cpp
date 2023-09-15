#include <iostream>
#include <queue>

int main() {
    for (int n{}, k{}; std::cin >> n >> k;) {
        std::priority_queue<long long, std::vector<long long>, std::greater<>>
            pri_que;
        for (int i = 0; i < n; ++i) {
            long long v{};
            std::cin >> v;
            pri_que.emplace(v);
        }
        for (int i = 0; i < k; ++i) {
            auto v = pri_que.top();
            pri_que.pop();
            if (v % 2) {
                v *= 2;
            } else {
                v = v * 2 + 1;
            }
            pri_que.emplace(v);
        }
        long long ans = 0LL;
        for (; !pri_que.empty();) {
            ans += pri_que.top();
            pri_que.pop();
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
