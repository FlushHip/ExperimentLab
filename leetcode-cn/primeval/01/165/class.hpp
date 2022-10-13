class Solution {
public:
    int compareVersion(string version1, string version2) {
        auto v1 = dealString(version1), v2 = dealString(version2);
        unsigned int n = std::max(v1.size(), v2.size());
        v1.insert(v1.end(), n - v1.size() , 0);
        v2.insert(v2.end(), n - v2.size() , 0);

        if (std::equal(v1.begin(), v1.end(),
            v2.begin())) {
                return 0;
        }

        return std::lexicographical_compare(v1.begin(), v1.end()
            , v2.begin(), v2.end()) ? -1 : 1;
    }

    std::vector<int> dealString(const std::string &str) {
        std::vector<int> ans;

        unsigned int begin = 0;
        for (auto it = str.find_first_of('.', begin); it != std::string::npos
            ; it = str.find_first_of('.', begin)) {
            int num = std::stoi(str.substr(begin, it - begin));
            ans.push_back(num);
            begin = it + 1;
        }
        ans.push_back(std::stoi(str.substr(begin, str.size() - begin)));

        return ans;
    }
};
