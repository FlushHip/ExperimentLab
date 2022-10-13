class Solution {
public:
    int compress(vector<char>& chars) {
        int ans = 0, n = (int)chars.size(), sum = 1;
        int index = 0;
        char pre = chars[0];

        chars.push_back(0);
        for (int i = 1; i < n + 1; ++i) {
            if (chars[i] != pre) {
                ++ans;
                chars[index++] = pre;
                if (1 != sum) {
                    auto str = std::to_string(sum);
                    ans += str.size();
                    for (const auto c : str) {
                        chars[index++] = c;
                    }
                }
                sum = 1;
                pre = chars[i];
            } else {
                ++sum;
            }
        }
        for (int cnt = 0; cnt < n + 1 - index; ++cnt) {
            chars.pop_back();
        }

        return ans;
    }
};
