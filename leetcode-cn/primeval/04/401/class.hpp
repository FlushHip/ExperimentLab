class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        ans_.clear();
        std::bitset<10> leds(0);
        dfs(leds, 0, turnedOn);
        return ans_;
    }

    void dfs(std::bitset<10> &leds, int index, int res) {
        if (index == 10) {
            if (res) {
                return ;
            }
            auto str = leds.to_string();
            auto hour = std::bitset<4>(str.substr(0, 4)).to_ulong();
            auto min = std::bitset<6>(str.substr(4, 6)).to_ulong();
            if (hour > 11 || min > 59) {
                return ;
            }
            auto ans = std::to_string(hour);
            ans.push_back(':');
            if (min < 10) {
                ans.push_back('0');
            }
            ans.append(std::to_string(min));
            ans_.emplace_back(ans);

            return;
        }

        if (10 - index - 1 >= res) {
            leds.reset(index);
            dfs(leds, index + 1, res);
        }

        if (10 - index >= res) {
            leds.set(index);
            dfs(leds, index + 1, res - 1);
        }
    }
private:
    std::vector<std::string> ans_;
};
