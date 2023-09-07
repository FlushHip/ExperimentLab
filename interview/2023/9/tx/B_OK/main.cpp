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
    for (int i = 0; i < n - 2; ++i) {
        int lhs = i + 1, rhs = n - 1;
        while (lhs < rhs) {
            if (arr[i] + arr[lhs] + arr[rhs] == 0) {
                if (rhs - lhs <= 2 || arr[lhs] != arr[lhs + 1] ||
                    arr[rhs] != arr[rhs - 1]) {
                    ans.emplace_back(arr[i], arr[lhs], arr[rhs]);
                }
                --rhs;
                ++lhs;
            } else if (arr[i] + arr[lhs] + arr[rhs] > 0) {
                --rhs;
            } else {
                ++lhs;
            }
        }
    }
    dbg(ans);
    return 0;
}
