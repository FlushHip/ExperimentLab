#include <algorithm>
#include <cctype>
#include <initializer_list>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

int main() {
    for (int n{}; std::cin >> n;) {
        std::string name, address;
        std::unordered_map<std::string, std::unordered_set<std::string>>
            ust_addr;
        std::map<std::string, std::pair<std::string, int>> ctxs;
        auto valid = [](std::initializer_list<std::string_view>&& strs) {
            return std::all_of(
                strs.begin(), strs.end(), [](std::string_view str) {
                    return std::all_of(str.begin(), str.end(), ::islower);
                });
        };
        for (int i = 0; i < n; ++i) {
            std::cin >> name >> address;
            if (!valid({name, address})) {
                continue;
            }
            if (ust_addr[address].contains(name)) {
                continue;
            }
            ust_addr[address].emplace(name);
            if (!ctxs.contains(name)) {
                ctxs.insert({name, {address, 0}});
            } else {
                ++ctxs[name].second;
            }
        }
        for (auto&& [name, pr] : ctxs) {
            auto&& [addr, cnt] = pr;
            std::cout << name << " " << addr << " " << cnt << std::endl;
        }
    }
    return 0;
}
