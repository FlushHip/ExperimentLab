#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    std::vector<int> arr(10);
    for ( ; ; ) {
        for (int i = 0; i < 10; ++i) {
            if (!(std::cin >> arr[i]))
                goto EXIT;
        }
        auto mid = std::partition(arr.begin(), arr.end(), [](const auto &value)
        {
            return value % 2;
        });
        std::sort(arr.begin(), mid, std::greater<int>());
        std::sort(mid, arr.end(), std::less<int>());
        for (int i = 0; i < 10; ++i)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
    }
    EXIT:;
    return 0;
}