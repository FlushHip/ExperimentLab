class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int n = (int)data.size();
        for (int i = 0; i < n; ) {
            if ((data[i] >> 7) == 0b0) {
                i += 1;
            } else if ((data[i] >> 5) == 0b110
                && (i + 1 < n && (data[i + 1] >> 6) == 0b10)) {
                i += 2;
            } else if ((data[i] >> 4) == 0b1110
                && (i + 1 < n && (data[i + 1] >> 6) == 0b10)
                && (i + 2 < n && (data[i + 2] >> 6) == 0b10)) {
                i += 3;
            } else if ((data[i] >> 3) == 0b11110
                && (i + 1 < n && (data[i + 1] >> 6) == 0b10)
                && (i + 2 < n && (data[i + 2] >> 6) == 0b10)
                && (i + 3 < n && (data[i + 3] >> 6) == 0b10)) {
                i += 4;
            } else {
                return false;
            }
        }
        return true;
    }
};
