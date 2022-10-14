class Solution {
public:
    int findLUSlength(string a, string b) {
        if (a.size() != b.size()) {
            return (int)std::max(a.size(), b.size());
        }
        return a == b ? -1 : (int)a.size();
    }
};
