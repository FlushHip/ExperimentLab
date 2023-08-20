#include <iostream>
#include <unordered_map>
#include <unordered_set>

int main() {
    for (int n{}; std::cin >> n;) {
        std::unordered_map<std::string, int> ump;
        std::unordered_set<std::string> ust;

        std::string word;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> word;
            ++ump[word];
            if (ump[word] == ans + 1 && ust.count(word) == 0) {
                ++ans;
                ust.emplace(word);
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
