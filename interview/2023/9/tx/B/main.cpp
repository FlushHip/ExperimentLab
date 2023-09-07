#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include <dbg.h>

int main() {
    std::vector<int> arr{-1, 0, 1, 2, 1, 4};
    int n = static_cast<int>(arr.size());
    std::sort(arr.begin(), arr.end());
    std::vector<std::tuple<int, int, int>> ans;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int target = -(arr[i] + arr[j]);
            // auto it = std::lower_bound(arr.begin() + j + 1, arr.end(),
            // target);
            auto pr = std::equal_range(arr.begin() + j + 1, arr.end(), target);
            for (auto it = pr.first; it != pr.second; ++it) {
                ans.emplace_back(arr[i], arr[j], *it);
            }
        }
    }
    dbg(ans);
    return 0;
}
