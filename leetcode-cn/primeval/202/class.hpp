class Solution {
public:
    bool isHappy(int n) {
        std::set<int> has;
        do {
            auto digit_str = std::to_string(n);
            n = std::accumulate(digit_str.begin(), digit_str.end(), 0, [](const auto ans, const auto c)
            {
                return ans + (c - '0') * (c - '0');
            });
            if (has.find(n) != has.end()) {
                return false;
            }
            has.insert(n);
        } while(n != 1);
        return true;
    }
};
