#include <iostream>
#include <map>

#include <dbg.h>

int main() {
    for (long long q{}, seed{}; std::cin >> q >> seed;) {
        auto gen = [&]() -> std::tuple<long long, long long, long long> {
            seed = seed ^ (seed << 15);
            seed = seed ^ (seed >> 5);
            seed = seed ^ (seed << 1);
            seed = seed % (1 << 15);

            long long op = (seed ^ (seed << 7) ^ (seed >> 5)) % 3 + 1;
            long long m = (seed ^ (seed << 6) ^ (seed >> 10)) % q + 1;
            long long x =
                (seed ^ (seed << 5) ^ (seed << 9) ^ (seed >> 6)) % 10 + 1;
            return {op, m, x};
        };
        long long ans = 0;
        std::map<long long, long long> mp;
        for (int i = 1; i <= q; ++i) {
            auto [op, m, x] = dbg(gen());
            if (op == 1) {
                ++mp[x];
            }
            if (op == 2) {
                auto it = mp.find(x);
                if (it != mp.end()) {
                    it->second -= std::min(m, it->second);
                    if (it->second == 0) {
                        mp.erase(it);
                    }
                }
            }
            if (op == 3) {
                if (!mp.empty()) {
                    ans = ans ^ (i * (mp.rbegin()->first - mp.begin()->first));
                }
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
