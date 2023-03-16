#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i];
        std::sort(arr.begin(), arr.end());
        std::cout << arr.back() << std::endl;
        if (arr.size() == 1u)
            std::cout << -1;
        else {
            for (int i = 0; i < n - 1; ++i)
                std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}