#include <iostream>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }
        int x{}, y{};
        std::cin >> x >> y;
        int pos = 0;
        for (; pos < n && arr[pos] != x; ++pos) {
        }
        if ((pos + 1 < n && arr[pos + 1] == y) ||
            (pos - 1 >= 0 && arr[pos - 1] == y)) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
        }
    }
    return 0;
}
