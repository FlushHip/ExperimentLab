#include <iostream>
#include <string>
#include <unordered_set>

int main(int argc, char **argv)
{
    for (int m, n; std::cin >> m; ) {
        std::unordered_set<std::string> st;
        for (int i = 0; i < m; ++i) {
            std::string ip;
            std::cin >> ip;
            st.insert(ip);
        }
        std::unordered_set<std::string> backup;

        int ans = 0;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::string ip;
            std::cin >> ip;
            auto it = st.find(ip);
            if (it == st.end())
                continue;
            backup.insert(ip);
            if (backup.size() == st.size()) {
                if (st.size() == 1) {
                    ans = -1;
                    continue;
                }
                backup.clear();
                backup.insert(ip);
                ++ans;
            }
        }

        std::cout << ans << std::endl;
    }
    return 0;
}