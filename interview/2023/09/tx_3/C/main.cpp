#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

int main() {
    for (int n{}, k{}; std::cin >> n >> k;) {
        std::unordered_map<long long,
            std::pair<long long,
                std::priority_queue<long long, std::vector<long long>,
                    std::greater<>>>>
            ump;
        for (int i = 0; i < n; ++i) {
            long long v{};
            std::cin >> v;
            ++ump[v].first;
            ump[v].second.emplace(i + 1);
        }
        std::vector<std::pair<long long,
            std::priority_queue<long long, std::vector<long long>,
                std::greater<>>>>
            a(1);
        for (auto&& [_, pr] : ump) {
            a.emplace_back(pr);
        }
        std::sort(a.begin(), a.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
        });
        int size = static_cast<int>(a.size());
        long long sum = 0;
        long long ans_min = 0, ans_value = 0;
        for (int i = 0; i < size; ++i) {
            if (sum + a[i].first * (size - i + 1) + k >= n) {
                ans_min = a[i].first;
                for (int j = i; j < size; ++j) {
                    for (int L = 0; L < a[j].first - a[i].first; ++L) {
                        ans_value += a[j].second.top();
                        a[j].second.pop();
                    }
                }
                break;
            }
            sum += a[i].first;
        }
        std::cout << ans_min << " " << ans_value << std::endl;
    }
    return 0;
}
