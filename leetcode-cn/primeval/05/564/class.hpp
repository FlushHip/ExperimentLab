class Solution {
public:
    string nearestPalindromic(string n) {
        int len = (int)n.size();
        std::vector<long long> candidates{
            (long long)(std::pow(10, len - 1) - 1),
            (long long)(std::pow(10, len) + 1),
        };

        auto prefix = std::stol(n.substr(0, (len + 1) / 2));
        for (const auto i : { prefix - 1, prefix, prefix + 1 }) {
            auto prefix_str = std::to_string(i);
            auto candidate = prefix_str + std::string(prefix_str.rbegin() + (len % 2), prefix_str.rend());
            candidates.push_back(std::stoll(std::move(candidate)));
        }

        std::sort(candidates.begin(), candidates.end());
        long long d = std::numeric_limits<long long>::max(), ans = 0, digit_n = std::stoll(n);
        for (const auto i : candidates) {
            auto dd = std::abs(digit_n - i);
            if (dd && dd < d) {
                d = dd;
                ans = i;
            }
        }
        return std::to_string(ans);
    }
};
