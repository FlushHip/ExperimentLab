#include <algorithm>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (long long n{}, t{}; std::cin >> n >> t;) {
        std::vector<std::pair<long long, long long>> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i].first;
            arr[i].second = n - i;
        }
        dbg(arr);
        for (int i = 0; i < n; ++i) {
            long long v{};
            std::cin >> v;
            arr[i].first += t * v;
        }
        std::sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.first < rhs.first;
        });
        dbg(arr);
        int ans = 1 < arr[n - 1].second, sum = 0;
        for (int i = n - 2; i >= 0; --i) {
            if (arr[i].first != arr[i + 1].first) {
                sum = n - 1 - i;
            }
            ans += sum + 1 < arr[i].second;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
