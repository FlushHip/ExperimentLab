#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<std::pair<int, int>> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i].second >> arr[i].first;
        std::sort(arr.begin(), arr.end());
        for (int i = 0; i < n; ++i)
            std::cout << arr[i].second << " " << arr[i].first << std::endl;
    }
    return 0;
}