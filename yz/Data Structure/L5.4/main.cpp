#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i];
        std::reverse(arr.begin(), arr.end());
        std::cout << arr[0];
        for (auto i = 1u; i < arr.size(); ++i)
            std::cout << ' ' << arr[i];
        std::cout << std::endl;
    }
    return 0;
}