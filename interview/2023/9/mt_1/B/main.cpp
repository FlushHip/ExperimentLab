#include <iostream>

int main() {
    for (int n{}; std::cin >> n;) {
        std::string s, t;
        std::cin >> s >> t;
        std::string s_, t_;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == t[i]) {
                ++ans;
            } else {
                s_.push_back(s[i]);
                t_.push_back(t[i]);
            }
        }
        int m = n - ans;
        bool f = false;
        for (int i = 0; i < m && !f; ++i) {
            for (int j = i + 1; j < m; ++j) {
                if (s_[i] == t_[j] && t_[i] == s_[j]) {
                    ans += 2;
                    f = true;
                    break;
                }
            }
        }
        if (!f) {
            for (int i = 0; i < m && !f; ++i) {
                for (int j = i + 1; j < m; ++j) {
                    if (s_[i] == t_[j]) {
                        ++ans;
                        f = true;
                        break;
                    }
                }
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
