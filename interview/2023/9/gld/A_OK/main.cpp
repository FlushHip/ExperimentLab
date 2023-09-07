#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

#include <dbg.h>

struct context {
    long long s{}, t{}, a{};
};

std::ostream& operator<<(std::ostream& os, const context& ctx) {
    auto [s, t, a] = ctx;
    os << "{" << s << ", " << t << ", " << a << "}";
    return os;
}

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<context> ctx(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> ctx[i].s;
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> ctx[i].t;
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> ctx[i].a;
        }
        std::sort(ctx.begin(), ctx.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.s + lhs.t < rhs.s + rhs.t;
        });
        dbg(ctx);
        std::vector<long long> dp(n);
        dp[0] = ctx[0].a;
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1];
            auto it = std::upper_bound(ctx.begin(), ctx.begin() + i, ctx[i].s,
                [](long long s, const auto& cx) { return s < cx.s + cx.t; });
            if (it != ctx.begin()) {
                dp[i] =
                    std::max(dp[i], dp[std::prev(it) - ctx.begin()] + ctx[i].a);
            } else {
                dp[i] = std::max(dp[i], ctx[i].a);
            }
        }
        dbg(dp);
        std::cout << dp[n - 1] << std::endl;
    }
    return 0;
}
