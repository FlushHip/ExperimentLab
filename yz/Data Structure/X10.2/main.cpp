#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    for (int n, k; std::cin >> n; ) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i];
        std::cin >> k;
        std::sort(arr.begin(), arr.end());
        auto last = std::unique(arr.begin(), arr.end());
        std::sort(arr.begin(), last);
        std::cout << arr[k - 1] << std::endl;
    }
    return 0;
}