#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

int main(int argc, char **argv)
{
    enum node_index {
        kString = 0,
        kSteps = 1,
    };
    int n; std::string str;
    for (; std::cin >> n >> str; ) {
        if (!(1 <= std::count(str.begin(), str.end(), '0')
                && 1 <= std::count(str.begin(), str.end(), '1')
                && 2 <= std::count(str.begin(), str.end(), '2'))) {
            std::cout << -1 << std::endl;
            continue;
        }

        std::queue<std::pair<std::string, int>> que;
        std::unordered_set<std::string> status;
        que.emplace(str, 0);
        status.insert(str);

        int ans = -1;
        while (!que.empty()) {
            auto top = que.front();
            que.pop();
            if (std::string::npos != std::get<node_index::kString>(top).find("2012")) {
                ans = std::get<node_index::kSteps>(top);
                break;
            }
            for (auto i = 1u; i < std::get<node_index::kString>(top).size(); ++i) {
                std::string s = std::get<node_index::kString>(top);
                if (s[i - 1] == s[i])
                    continue;
                std::swap(s[i - 1], s[i]);
                if (status.end() != status.find(s))
                    continue;
                que.emplace(s, std::get<node_index::kSteps>(top) + 1);
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}