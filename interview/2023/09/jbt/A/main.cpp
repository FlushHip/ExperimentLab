#include <algorithm>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    std::vector<int> a{6, 6, 9, 1, 2, 4, 7};
    dbg(a);
    int n = static_cast<int>(a.size());
    std::sort(a.begin(), a.end());
    dbg(a);
    std::vector<int> targets{0, 2};
    for (const auto t : targets) {
        int lhs = 0, rhs = n;
        while (lhs < rhs) {
            int mid = (lhs + rhs) / 2;
            if (a[mid] == t) {
                std::cout << "find " << t << std::endl;
                break;
            }
            if (a[mid] < t) {
                lhs = mid + 1;
            } else {
                rhs = mid - 1;
            }
        }
        if (lhs == rhs) {
            std::cout << "not find " << t << std::endl;
        }
    }
    return 0;
}
