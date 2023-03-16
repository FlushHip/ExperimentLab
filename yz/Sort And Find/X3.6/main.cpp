#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i];
        for (int i = 0; i < n; ++i) {
            if ((i == 0 && arr[i] != arr[i + 1])
                || (i + 1 == n && arr[i] != arr[i - 1])
                || (i != 0 && i + 1 != n && arr[i] > arr[i - 1] && arr[i] > arr[i + 1])
                || (i != 0 && i + 1 != n && arr[i] < arr[i - 1] && arr[i] < arr[i + 1]))
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}