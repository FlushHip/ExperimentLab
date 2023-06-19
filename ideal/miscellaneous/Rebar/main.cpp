#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <prettyprint.hpp>

constexpr int kunit = 50;

int main(int argc, char* argv[]) {
    std::ifstream fin("./in.dat", std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "file isn't open" << std::endl;
        return -1;
    }

    struct info {
        int num = 0;
        std::string label;
        std::string rebar_d;
        std::string name;
        int len = 0;
    };
    std::map<std::string, std::vector<info>> mp_lines;
    while (true) {
        int num = 0;
        std::string label;
        std::string rebar_d;
        std::string name;
        int len = 0;
        int cnt = 0;
        if (!(fin >> num >> label >> rebar_d >> name >> len >> cnt)) {
            break;
        }
        if (rebar_d == "8") {
            continue;
        }
        while (cnt--) {
            mp_lines[rebar_d].emplace_back(
                info{num, label, rebar_d, name, len / kunit});
        }
    }

    for (auto&& [rebar_d, lines] : mp_lines) {
        const int total_len = 12000 / kunit;
        std::vector<std::pair<info, size_t>> last;
        for (size_t i = 0; i < lines.size(); ++i) {
            last.emplace_back(lines[i], i);
        }

        struct result_t {
            struct raber_line_n {
                int total_len;
                int rest_len;
                std::vector<size_t> idxs;
            };
            std::vector<raber_line_n> raber_line;
            int cnt{};
        } result;

        for (; !last.empty();) {
            int n = static_cast<int>(last.size());
            std::vector<std::vector<int>> dp(
                n, std::vector<int>(total_len + 1));
            for (int w = last[0].first.len; w <= total_len; ++w) {
                dp[0][w] = last[0].first.len;
            }
            for (int i = 1; i < n; ++i) {
                dp[i] = dp[i - 1];
                for (int w = last[i].first.len; w <= total_len; ++w) {
                    if (dp[i][w] <
                        dp[i - 1][w - last[i].first.len] + last[i].first.len) {
                        dp[i][w] = dp[i - 1][w - last[i].first.len] +
                            last[i].first.len;
                    }
                }
            }
            int rest = dp[n - 1][total_len];
            std::vector<size_t> idxs;
            for (int i = n - 1; i > 0 && rest; --i) {
                if (rest == dp[i - 1][rest]) {
                    continue;
                }
                idxs.push_back(last[i].second);
                rest -= last[i].first.len;
            }
            if (rest != 0) {
                idxs.push_back(last[0].second);
            }

            for (auto idx : idxs) {
                last.erase(std::find_if(last.begin(), last.end(),
                    [idx](auto& pr) { return pr.second == idx; }));
            }

            ++result.cnt;
            result.raber_line.push_back(result_t::raber_line_n{
                dp[n - 1][total_len] * kunit,
                (total_len - dp[n - 1][total_len]) * kunit, std::move(idxs)});
        }

        std::cout << "rebar_d : " << rebar_d << " | cnt :" << lines.size()
                  << std::endl;
        std::cout << "-----------------------------------------------"
                  << std::endl;
        for (int i = 0; i < result.cnt; ++i) {
            std::cout << "No." << i + 1 << "\t" << total_len * kunit << "\t"
                      << result.raber_line[i].total_len << "\t"
                      << result.raber_line[i].rest_len << "\t";
            std::vector<std::tuple<int, std::string, std::string, int>> items;
            for (auto idx : result.raber_line[i].idxs) {
                items.emplace_back(lines[idx].num, lines[idx].label,
                    lines[idx].name, lines[idx].len * kunit);
            }

            std::cout << items.size() << "\t" << items << std::endl;
        }
        std::cout << "==============================================="
                  << std::endl;
        std::cout << "12m's : " << result.cnt << "\t"
                  << "9m's : 0" << std::endl;
        std::cout << "-----------------------------------------------"
                  << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
