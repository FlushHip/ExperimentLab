#include <iostream>
#include <string>
#include <vector>

#include <dbg.h>

int main() {
    for (std::string line; std::cin >> line;) {
        line.push_back(',');
        std::vector<int> arr;
        size_t begin = 0;
        for (auto pos = line.find(',', begin); pos != std::string::npos;
             pos = line.find(',', begin)) {
            arr.emplace_back(std::stoi(
                std::string{line.begin() + begin, line.begin() + pos}));
            begin = pos + 1;
        }
        dbg(arr);
        int n = static_cast<int>(arr.size());
        std::vector<int> dp(n, 0);
        dp[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (arr[i] < arr[i - 1]) {
                dp[i] = 1 + dp[i - 1];
            } else {
                dp[i] = 1;
            }
        }
        std::cout << dp[n - 1] << std::endl;
    }
    return 0;
}
