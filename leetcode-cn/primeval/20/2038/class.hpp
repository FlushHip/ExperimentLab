class Solution {
public:
    bool winnerOfGame(string colors) {
        int A = 0, B = 0;
        for (std::string::size_type begin = 0; begin != std::string::npos; ) {
            auto end = colors.find_first_not_of(colors[begin], begin);
            auto d = std::max(0, (int)((end == std::string::npos ? colors.size() : end) - begin - 2));
            if (colors[begin] == 'A') {
                A += d;
            } else {
                B += d;
            }
            begin = end;
        }
        return A > B;
    }
};
