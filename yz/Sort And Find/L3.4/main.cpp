#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            std::cin >> arr[i];
        int x = 0;
        std::cin >> x;
        int ans = -1;
        for (int i = 0; i < n; ++i)
            if (arr[i] == x) {
                ans = i;
                break;
            }
        std::cout << ans << std::endl;
    }
    return 0;
}