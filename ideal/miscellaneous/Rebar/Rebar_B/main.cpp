#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <ostream>
#include <unordered_map>
#include <vector>

#include <dbg.h>
#include <prettyprint.hpp>

constexpr int krebar_length = 9000;
constexpr int kunit = 10;

int main(int /*argc*/, char* /*argv*/[]) {
    std::ifstream fin("./in.dat", std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "file isn't open" << std::endl;
        return -1;
    }
    std::string file_path = "./out.dat";
    std::ofstream fout(dbg(file_path));

    std::string file_path_ban_map = "./out2.dat";
    std::ofstream fout2(dbg(file_path_ban_map));

    struct info {
        std::string num;
        std::string position_main;
        std::string position_2;
        std::string rebar_d;
        std::string name;
        int len = 0;
    };
    for (int n{}; fin >> n; fout
         << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
            "++++++++++++++"
         << std::endl
         << std::endl) {
        std::map<std::string, std::vector<info>> mp_lines;
        // 8
        std::map<int, int> g_cnts;
        while (n--) {
            std::string num;
            std::string position_main;
            std::string position_2;
            std::string rebar_d;
            std::string name;
            int len = 0;
            int cnt = 0;
            if (!(fin >> num >> position_main >> position_2 >> rebar_d >>
                    name >> len >> cnt)) {
                break;
            }
            if (rebar_d == "8") {
                g_cnts[len] += cnt;
                continue;
            }
            while (cnt--) {
                mp_lines[rebar_d].emplace_back(info{num, position_main,
                    position_2, rebar_d, name, len / kunit});
            }
        }

        int cnt_rebar_d_9 = 0;
        int cnt_rebar_d_12 = 0;

        struct context {
            std::vector<int> line;
            int cnt;
            int sum;
            int rest;
            bool operator==(const context& other) const {
                return cnt == other.cnt &&
                    std::equal(line.begin(), line.end(), other.line.begin());
            }
        };
        /*
        struct hash {
            std::size_t operator()(const context& ctx) const {
                constexpr long long mod = 1e9 + 7;
                long long base = 9973, m = 1;
                std::size_t result = 0;
                for (auto n : ctx.line) {
                    result = (result + m * n % mod) % mod;
                    m = (m * base) % mod;
                }
                return result;
            }
        };
        std::unordered_map<context, int, hash> ban_map;
        */

        // use std::map to avoid sort
        auto ctx_cmp = [](const context& lhs, const context& rhs) {
            if (lhs.sum == rhs.sum) {
                if (lhs.cnt == rhs.cnt) {
                    for (int i = 0; i < lhs.cnt; ++i) {
                        if (lhs.line[i] == rhs.line[i]) {
                            continue;
                        }
                        return lhs.line[i] < rhs.line[i];
                    }
                    return false;
                }
                return lhs.cnt > rhs.cnt;
            }
            return lhs.sum > rhs.sum;
        };
        std::map<context, int, decltype(ctx_cmp)> ban_map(ctx_cmp);

        for (auto&& [rebar_d, lines] : mp_lines) {
            const int total_len =
                (std::stod(rebar_d) > 10 ? 12000 : krebar_length) / kunit;
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

            bool need_ban_map = rebar_d == "10";
            if (need_ban_map) {
                ban_map.clear();
                fout2 << "----------------------------------------------------"
                      << std::endl;
            }

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
                        if (dp[i][w] < dp[i - 1][w - last[i].first.len] +
                                last[i].first.len) {
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
                result.raber_line.push_back(
                    result_t::raber_line_n{dp[n - 1][total_len] * kunit,
                        (total_len - dp[n - 1][total_len]) * kunit,
                        std::move(idxs)});
            }

            fout << "rebar_d : " << dbg(rebar_d) << " | cnt :" << lines.size()
                 << std::endl;
            fout << "-----------------------------------------------"
                 << std::endl;
            int cnt_12 = 0;
            int cnt_9 = 0;
            for (int i = 0; i < result.cnt; ++i) {
                int rebar_to_use =
                    result.raber_line[i].total_len > 9000 ? 12000 : 9000;
                int total_len = result.raber_line[i].total_len;
                int rest_len = rebar_to_use - total_len;
                if (rebar_to_use == 12000) {
                    ++cnt_12;
                } else {
                    ++cnt_9;
                }
                fout << "No." << i + 1 << "\t" << rebar_to_use << "\t"
                     << total_len << "\t" << rest_len << "\t";
                std::vector<
                    std::tuple<std::string, std::string, std::string, int>>
                    items;
                for (auto idx : result.raber_line[i].idxs) {
                    items.emplace_back(lines[idx].num, lines[idx].position_main,
                        lines[idx].name, lines[idx].len * kunit);
                }

                fout << items.size() << "\t" << items << std::endl;

                if (need_ban_map) {
                    std::vector<int> line;
                    for (auto idx : result.raber_line[i].idxs) {
                        line.emplace_back(lines[idx].len * kunit);
                    }
                    std::sort(line.begin(), line.end());
                    int t_cnt = static_cast<int>(line.size());
                    int t_sum = std::accumulate(line.begin(), line.end(), 0);
                    int t_rest = 9000 - t_sum;
                    auto ctx = context{std::move(line), t_cnt, t_sum, t_rest};
                    ++ban_map[ctx];
                }
            }
            cnt_rebar_d_12 += cnt_12;
            cnt_rebar_d_9 += cnt_9;
            fout << "==============================================="
                 << std::endl;
            fout << "12m's : " << dbg(cnt_12) << "\t"
                 << "9m's : " << dbg(cnt_9) << std::endl;
            fout << "-----------------------------------------------"
                 << std::endl;
            fout << std::endl;

            if (need_ban_map) {
                auto index = 0, sum_cnt = 0;
                for (const auto& [ctx, cnt] : ban_map) {
                    fout2 << ++index << "\t" << cnt << "\t" << 9 << "\t"
                          << ctx.sum << "\t" << ctx.cnt << "\t" << ctx.line
                          << "\t" << ctx.rest << std::endl;
                    sum_cnt += cnt;
                }
                fout2 << "-------> " << sum_cnt << std::endl;
            }
        }

        fout << "-----------------------------------------------" << std::endl;
        fout << "total : "
             << "12m's : " << dbg(cnt_rebar_d_12) << "\t"
             << "9m's : " << dbg(cnt_rebar_d_9) << std::endl;

        fout << "g :" << std::endl;
        for (const auto& [len, cnt] : dbg(g_cnts)) {
            fout << "  " << len << " " << cnt << std::endl;
        }
    }

    return 0;
}
