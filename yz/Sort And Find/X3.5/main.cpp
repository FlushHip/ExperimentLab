#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<std::pair<int, int>> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i].first >> arr[i].second;
        std::sort(arr.begin(), arr.end());
        std::cout << arr.front().first << " " << arr.front().second << std::endl;
    }
    return 0;
}