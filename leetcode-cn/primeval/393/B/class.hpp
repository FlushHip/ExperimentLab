class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int n = (int)data.size();
        for (int i = 0; i < n; ) {
            if ((data[i] >> 7) == 0x0) {
                i += 1;
            } else if ((data[i] >> 5) == 0x6
                && (i + 1 < n && (data[i + 1] >> 6) == 0x2)) {
                i += 2;
            } else if ((data[i] >> 4) == 0xE
                && (i + 1 < n && (data[i + 1] >> 6) == 0x2)
                && (i + 2 < n && (data[i + 2] >> 6) == 0x2)) {
                i += 3;
            } else if ((data[i] >> 3) == 0x1E
                && (i + 1 < n && (data[i + 1] >> 6) == 0x2)
                && (i + 2 < n && (data[i + 2] >> 6) == 0x2)
                && (i + 3 < n && (data[i + 3] >> 6) == 0x2)) {
                i += 4;
            } else {
                return false;
            }
        }
        return true;
    }
};
