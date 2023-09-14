#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <vector>

#include <dbg.h>
#include <prettyprint.hpp>

constexpr int krebar_length = 12000;
constexpr int kunit = 50;

int main(int /*argc*/, char* /*argv*/[]) {
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
    // G
    std::map<int, int> g_cnts;
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
            g_cnts[len] += cnt;
            continue;
        }
        while (cnt--) {
            mp_lines[rebar_d].emplace_back(
                info{num, label, rebar_d, name, len / kunit});
        }
    }

    int cnt_rebar_d_9 = 0;
    int cnt_rebar_d_12 = 0;
    std::string file_path = "./out.dat";
    std::ofstream fout(dbg(file_path));
    for (auto&& [rebar_d, lines] : mp_lines) {
        const int total_len = krebar_length / kunit;
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

        fout << "rebar_d : " << dbg(rebar_d) << " | cnt :" << lines.size()
             << std::endl;
        fout << "-----------------------------------------------" << std::endl;
        int cnt_12 = 0;
        int cnt_9 = 0;
        for (int i = 0; i < result.cnt; ++i) {
            int rebar_to_use =
                result.raber_line[i].total_len > 9000 ? krebar_length : 9000;
            int total_len = result.raber_line[i].total_len;
            int rest_len = rebar_to_use - total_len;
            if (rebar_to_use == krebar_length) {
                ++cnt_12;
            } else {
                ++cnt_9;
            }
            fout << "No." << i + 1 << "\t" << rebar_to_use << "\t" << total_len
                 << "\t" << rest_len << "\t";
            std::vector<std::tuple<int, std::string, std::string, int>> items;
            for (auto idx : result.raber_line[i].idxs) {
                items.emplace_back(lines[idx].num, lines[idx].label,
                    lines[idx].name, lines[idx].len * kunit);
            }

            fout << items.size() << "\t" << items << std::endl;
        }
        cnt_rebar_d_12 += cnt_12;
        cnt_rebar_d_9 += cnt_9;
        fout << "===============================================" << std::endl;
        fout << "12m's : " << dbg(cnt_12) << "\t"
             << "9m's : " << dbg(cnt_9) << std::endl;
        fout << "-----------------------------------------------" << std::endl;
        fout << std::endl;
    }

    fout << "-----------------------------------------------" << std::endl;
    fout << "total : "
         << "12m's : " << dbg(cnt_rebar_d_12) << "\t"
         << "9m's : " << dbg(cnt_rebar_d_9) << std::endl;

    fout << "g :" << std::endl;
    for (const auto& [len, cnt] : dbg(g_cnts)) {
        fout << "  " << len << " " << cnt << std::endl;
    }

    return 0;
}
