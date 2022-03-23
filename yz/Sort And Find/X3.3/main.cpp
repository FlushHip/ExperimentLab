#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<std::pair<int, std::string>> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i].first >> arr[i].second;
        std::sort(arr.begin(), arr.end());
        for (auto it = arr.crbegin(); it != arr.crend(); ++it)
            std::cout << it->second << std::endl;
    }
    return 0;
}