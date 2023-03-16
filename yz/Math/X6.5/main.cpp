#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n && n; ) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i];
        std::sort(arr.begin(), arr.end());

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ans += std::gcd(arr[i], arr[j]) == 1;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}