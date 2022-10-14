class Solution {
public:
    string convertToBase7(int num) {
        std::array<char, 20> ans{ 0 };
        std::to_chars(ans.data(), ans.data() + ans.size(), num, 7);
        return ans.data();
    }
};
