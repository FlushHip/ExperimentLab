#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    for (int n, m = 0; std::cin >> n; ) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i];
        std::sort(arr.begin(), arr.end());
        for (std::cin >> m, n = 0; n < m; ++n) {
            int target = 0;
            std::cin >> target;
            std::cout << (std::binary_search(arr.begin(), arr.end(), target) ? "YES" : "NO") << std::endl;
        }
    }
    return 0;
}