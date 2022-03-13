class Solution {
    bool cmp(const std::string &digits_binary, int index) {
        std::regex reg;
        if (index == 0) {
            reg = "^[0]{24}0[0-1]{7}$";
        }
        if (index == 1) {
            reg = "^[0]{16}110[0-1]{5}10[0-1]{6}$";
        }
        if (index == 2) {
            reg = "^[0]{8}1110[0-1]{4}(10[0-1]{6}){2}$";
        }
        if (index == 3) {
            reg = "^11110[0-1]{3}(10[0-1]{6}){3}$";
        }
        return std::regex_match(digits_binary, reg);
    }
public:
    bool validUtf8(vector<int>& data) {
        int n = (int)data.size();
        std::bitset<32> digits;
        for (int i = 0; i < n; ) {
            digits.reset();
            bool f = false;
            for (int j = 0; j < 4 && i + j < n; ++j) {
                digits <<= 8;
                digits |= std::bitset<32>(data[i + j]);
                if (cmp(digits.to_string(), j)) {
                    i += j + 1;
                    f = true;
                    break;
                }
            }
            if (!f) {
                return false;
            }
        }
        return true;
    }
};
