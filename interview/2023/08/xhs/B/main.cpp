#include <iostream>
#include <vector>

int main() {
    for (int T{}; std::cin >> T;) {
        for (int L = 0; L < T; ++L) {
            std::string str;
            std::cin >> str;
            int n = static_cast<int>(str.size());
            std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
            for (int i = 0; i < n; ++i) {
                dp[i][i] = true;
            }
            for (int len = 2; len <= n; ++len) {
                for (int i = 0; i + len - 1 < n; ++i) {
                    int j = i + len - 1;
                    if (i + 1 > j - 1 || dp[i + 1][j - 1]) {
                        if (str[i] == str[j]) {
                            dp[i][j] = true;
                        } else if (((str[i] == 'b' || str[i] == 'd' ||
                                        str[i] == 'p' || str[i] == 'q') &&
                                       (str[j] == 'b' || str[j] == 'd' ||
                                           str[j] == 'p' || str[j] == 'q')) ||
                            ((str[i] == 'n' || str[i] == 'u') &&
                                (str[j] == 'n' || str[j] == 'u'))) {
                            dp[i][j] = true;
                        } else {
                            dp[i][j] = false;
                        }
                    } else {
                        dp[i][j] = false;
                    }
                    if (str[i] == 'w' && str[j] == 'v') {
                        if ((i >= j - 1 || str[j - 1] == 'v') &&
                            (i + 1 > j - 2 || dp[i + 1][j - 2])) {
                            dp[i][j] = true;
                        }
                    }
                    if (str[i] == 'v' && str[j] == 'w') {
                        if ((i + 1 >= j || str[i + 1] == 'v') &&
                            (i + 2 > j - 1 || dp[i + 2][j - 1])) {
                            dp[i][j] = true;
                        }
                    }

                    if (str[i] == 'm' && (str[j] == 'n' || str[j] == 'u')) {
                        if ((i >= j - 1 || str[j - 1] == 'n' ||
                                str[j - 1] == 'u') &&
                            (i + 1 > j - 2 || dp[i + 1][j - 2])) {
                            dp[i][j] = true;
                        }
                    }
                    if ((str[i] == 'n' || str[i] == 'u') && str[j] == 'm') {
                        if ((i + 1 >= j || str[i + 1] == 'n' ||
                                str[i + 1] == 'u') &&
                            (i + 2 > j - 1 || dp[i + 2][j - 1])) {
                            dp[i][j] = true;
                        }
                    }
                }
            }
            std::cout << (dp[0][n - 1] ? "YES" : "NO") << std::endl;
        }
    }
    return 0;
}
